/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:16:29 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/06/11 15:35:52 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	join_phi(t_philo *philo)
{
	ssize_t	i;
	int		err;

	i = 0;
	if (!philo)
		return (SUCCESS);
	while (i < philo->param->n_philo)
	{
		err = pthread_join(philo[i++].tid, NULL);
		if (err != 0)
		{
			printf("%d\n", err);
			return (derr("Error joining threads: ", NULL));
		}
	}
	pthread_mutex_destroy(&philo->param->init_lock);
	free(philo->param->arfork);
	free(philo);
	return (SUCCESS);
}

void	time_is_up(t_philo	*philarray)
{
	time_t	time;
	size_t	n_phi;
	size_t	i;

	i = 0;
	n_phi = philarray->param->n_philo;
	while (1)
	{
		pthread_mutex_lock(&philarray[i].time_lock);
		time = get_time_elapsed(philarray[i].last_ate);
		pthread_mutex_unlock(&philarray[i].time_lock);
		if (time >= philarray[i].param->t_to_die || all_fed(philarray))
		{
			pthread_mutex_lock(&philarray[i].param->init_lock);
			philarray[i].param->died = true;
			pthread_mutex_unlock(&philarray[i].param->init_lock);
			if (all_fed(philarray))
			{	
				printf("all philos ate n times\n");
				return ;
			}
			status_message(philarray + i, DEAD);
			return ;
		}
		i = (i + 1) % n_phi;
		usleep(10);
	}
}

int	main(int argc, char *argv[])
{
	t_param		param;
	t_philo		*philarray;

	philarray = NULL;
	if (argc > 6 || argc < 5)
		return (derr(INPUT_ERROR, NULL));
	if (init_params(&param, argv) == ERROR)
		return (ERROR);
	philarray = malloc((param.n_philo + 1) * sizeof (t_philo));
	if (!philarray)
		return (derr("Memory allocation issue", NULL));
	memset((t_philo *)philarray, 0, sizeof(t_philo));
	if (init_philo(&param, philarray) == ERROR)
	{
		join_phi(philarray);
		return (ERROR);
	}
	time_is_up(philarray);
	join_phi(philarray);
	return (SUCCESS);
}

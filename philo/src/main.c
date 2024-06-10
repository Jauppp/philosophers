/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jauseff <jauseff@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:16:29 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/06/08 01:34:00 by jauseff          ###   ########lyon.fr   */
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

void	time_is_up(t_philo	*philarr)
{
	time_t	time;
	size_t	n_phi;
	size_t	i;
	
	i = 0;
	n_phi = philarr->param->n_philo;
	while (1)
	{
		pthread_mutex_lock(&philarr[i].time_lock);
		time = get_time_elapsed(philarr[i].last_ate);
		pthread_mutex_unlock(&philarr[i].time_lock);
		// pthread_mutex_lock(&philarr[i].param->write_lock);
		// printf("time : %ld | t_to_die : %ld\n", time, philarr[i].param->t_to_die);
		// pthread_mutex_unlock(&philarr[i].param->write_lock);
		if (time >= philarr[i].param->t_to_die)
		{
			pthread_mutex_lock(&philarr[i].param->init_lock);
			philarr[i].param->died = true;
			pthread_mutex_unlock(&philarr[i].param->init_lock);
			status_message(philarr + i, DEAD);
			return ;
		}
		i = (i + 1) % n_phi;
		usleep(500);
	}
}

int	main(int argc, char *argv[])
{
	t_param		param;
	t_philo		*philarr;

	philarr = NULL;
	if (argc > 6 || argc < 5)
		return (derr(INPUT_ERROR, NULL));
	if (init_params(&param, argv) == ERROR)
		return (ERROR);
	philarr = malloc((param.n_philo + 1) * sizeof (t_philo));
	if (!philarr)
		return (derr("Memory allocation issue", NULL));
	memset((t_philo *)philarr, 0, sizeof(t_philo));
	if (init_philo(&param, philarr) == ERROR)
	{
		join_phi(philarr);
		return (ERROR);
	}
	time_is_up(philarr);
	join_phi(philarr);
	return (SUCCESS);
}

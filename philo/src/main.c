/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:16:29 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/06/06 14:04:11 by cdomet-d         ###   ########lyon.fr   */
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

void	time_is_up(t_param	*param)
{
	usleep(15000);
	pthread_mutex_lock(&param->init_lock);
	param->died = true;
	pthread_mutex_unlock(&param->init_lock);
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
	if (init_philo(&param, philarr) == ERROR)
	{
		join_phi(philarr);
		return (ERROR);
	}
	time_is_up(&param);
	join_phi(philarr);
	return (SUCCESS);
}

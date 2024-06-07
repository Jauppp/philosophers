/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:15:03 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/06/07 17:21:10 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Your(s) program(s) should take the following arguments:
	// - number_of_philosophers 
	// - time_to_die 
	// - time_to_eat 
	// - time_to_sleep
	// - [number_of_times_each_philosopher_must_eat

int	init_params(t_param	*param, char **args)
{
	if (isdigit_param(args) == ERROR)
		return (ERROR);
	param->n_philo = ft_atoi(args[1]);
	if (param->n_philo < 1)
		return (derr("Invalid argument: ", args[1]));
	param->t_to_die = ft_atoi(args[2]);
	if (param->t_to_die < 1)
		return (derr("Invalid argument: ", args[2]));
	param->t_to_eat = ft_atoi(args[3]);
	if (param->t_to_eat < 1)
		return (derr("Invalid argument: ", args[3]));
	param->t_to_sleep = ft_atoi(args[4]);
	if (param->t_to_sleep < 1)
		return (derr("Invalid argument: ", args[4]));
	if (args[5])
	{
		param->n_must_eat = ft_atoi(args[5]);
		if (param->t_to_sleep < 1)
			return (derr("Invalid argument: ", args[5]));
	}
	else
		param->n_must_eat = -1;
	param->start.tv_sec = 0;
	param->died = false;
	return (SUCCESS);
}

static int	init_fork(t_param *param)
{
	ssize_t	i;

	i = 0;
	param->arfork = malloc(param->n_philo * sizeof(t_fork));
	if (!param->arfork)
		return (ERROR);
	while (i < param->n_philo)
	{
		param->arfork[i] = create_t_fork();
		param->arfork[i].ifork = i;
		i++;
	}
	return (SUCCESS);
}

int	init_philo(t_param *param, t_philo *philarr)
{
	ssize_t		i;
	struct timeval	go;

	i = 0;
	if (init_fork(param) == ERROR)
		return (derr("Error allocating memory", NULL));
	pthread_mutex_init(&param->init_lock, NULL);
	while (i < param->n_philo)
	{
		philarr[i] = create_t_philo(i + 1, param);
		create_thread(philarr + i);
		if (philarr[i].tid == ERROR)
			return (ERROR);
		i++;
	}
	gettimeofday(&go, NULL);
	i = 0;
	while (i < param->n_philo)
	{
		pthread_mutex_lock(&philarr[i].time_lock);
		philarr[i].last_ate = go;
		pthread_mutex_unlock(&philarr[i].time_lock);
		i++;
	}
	pthread_mutex_lock(&param->init_lock);
	param->start = go;
	pthread_mutex_unlock(&param->init_lock);
	return (SUCCESS);
}

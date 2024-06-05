/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:15:03 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/06/04 17:27:26 by cdomet-d         ###   ########lyon.fr   */
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
	dpm(*param);
	return (SUCCESS);
}

static t_fork create_t_fork(void)
{
	t_fork	fork;

	fork.fork = true;
	pthread_mutex_init(&fork.mfork, NULL);
	return (fork);
}

static int init_fork(t_param *param)
{
	ssize_t	i;

	i = 0;
	param->arfork = malloc(param->n_philo * sizeof(t_fork));
	if (!param->arfork)
		return (ERROR);
	while (i < param->n_philo)
	{
		param->arfork[i] = create_t_fork();
		i++;
	}
	return (SUCCESS);
}

static t_philo	create_t_philo(int phid, t_param *param)
{
	t_philo	philo;
	
	philo.last_ate = 0;
	philo.nb_ate = 0;
	philo.param = param;
	philo.phid = phid;
	if (phid == param->n_philo)
	{
		philo.fork[0] = param->arfork[0];
		philo.fork[1] = param->arfork[phid - 1];
	}
	else
	{
		philo.fork[0] = param->arfork[phid - 1];
		philo.fork[1] = param->arfork[phid];
	}
	return (philo);
}

static void create_thread(t_philo *philo)
{
	//TODO: check leaks when pthread_create fails
	if (pthread_create(&philo->tid, NULL, routine, (void *)philo) != 0)
		return ;
}

int	init_philo(t_param *param, t_philo *philo)
{
	ssize_t		i;
	
	i = 0;
	if (init_fork(param) == ERROR)
		return (derr("Error allocating memory", NULL));
	pthread_mutex_init(&param->init_lock, NULL);
	param->end = false;
	while (i < param->n_philo)
	{
		philo[i] = create_t_philo(i + 1, param);
		create_thread(philo + i);
		if (philo[i].tid == ERROR)
			return (ERROR);
		i++;
	}
	pthread_mutex_lock(&param->init_lock);
	param->end = true;
	pthread_mutex_unlock(&param->init_lock);
	return (SUCCESS);
}

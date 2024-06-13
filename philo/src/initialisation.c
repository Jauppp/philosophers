/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:15:03 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/06/13 13:12:40 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_mutexes(pthread_mutex_t *mutex_1, pthread_mutex_t *mutex_2)
{
	if (pthread_mutex_init(mutex_1, NULL) != 0)
		return (derr("Error initialising mutex", NULL));
	if (pthread_mutex_init(mutex_2, NULL) != 0)
		return (derr("Error initialising mutex", NULL));
	return (SUCCESS);
}

int	init_args(t_arg	*arg, char **args)
{
	if (isdigit_param(args) == ERROR)
		return (ERROR);
	arg->n_philo = _atoi(args[1]);
	if (arg->n_philo < 1)
		return (derr("Invalid argument: ", args[1]));
	arg->t_die = _atoi(args[2]);
	if (arg->t_die < 1)
		return (derr("Invalid argument: ", args[2]));
	arg->t_eat = _atoi(args[3]);
	if (arg->t_eat < 1)
		return (derr("Invalid argument: ", args[3]));
	arg->t_sleep = _atoi(args[4]);
	if (arg->t_sleep < 1)
		return (derr("Invalid argument: ", args[4]));
	if (args[5])
	{
		arg->max_meals = _atoi(args[5]);
		if (arg->max_meals < 1)
			return (derr("Invalid argument: ", args[5]));
	}
	else
		arg->max_meals = -1;
	memset(&arg->start, 0, sizeof (struct timeval));
	arg->died = false;
	return (SUCCESS);
}

static int	init_fork(t_arg *arg)
{
	ssize_t	i;

	i = 0;
	arg->arfork = malloc(arg->n_philo * sizeof(t_fork));
	if (!arg->arfork)
		return (ERROR);
	memset((t_fork *)arg->arfork, 0, sizeof(t_fork));
	while (i < arg->n_philo)
	{
		arg->arfork[i] = create_t_fork();
		if (pthread_mutex_init(&arg->arfork[i].mfork, NULL) != 0)
			return (free(arg->arfork), derr("Error initialising mutex", NULL));
		arg->arfork[i].init_success = true;
		i++;
	}
	return (SUCCESS);
}

int	init_philo(t_arg *arg, t_philo *pharr)
{
	ssize_t	i;

	i = -1;
	if (init_fork(arg) == ERROR)
		return (derr("Error initialising fork array", NULL));
	if (init_mutexes(&arg->init_lock, &arg->write_lock) != 0)
		return (free(arg->arfork), ERROR);
	while (++i < arg->n_philo)
	{
		pharr[i] = create_t_philo(i + 1, arg);
		if (init_mutexes(&pharr[i].time_lock, &pharr[i].var_lock) != 0)
			return (free(arg->arfork), derr("Error initialising mutex", NULL));
		if (create_thread(pharr + i) != 0)
		{
			arg->n_philo = i;
			return (free(arg->arfork), ERROR);
		}
	}
	get_starting_time(pharr, arg);
	return (SUCCESS);
}

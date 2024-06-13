/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 10:55:03 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/06/13 13:11:00 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_fork	create_t_fork(void)
{
	t_fork	fork;

	fork.fork = true;
	return (fork);
}

t_philo	create_t_philo(int phid, t_arg *arg)
{
	t_philo	philo;

	philo.nb_ate = 0;
	philo.tid = 0;
	philo.arg = arg;
	philo.phid = phid;
	if (phid == arg->n_philo)
	{
		philo.fork[1] = &arg->arfork[0];
		philo.fork[0] = &arg->arfork[phid - 1];
	}
	else
	{
		philo.fork[0] = &arg->arfork[phid - 1];
		philo.fork[1] = &arg->arfork[phid];
	}
	return (philo);
}

int	create_thread(t_philo *philo)
{
	return (pthread_create(&philo->tid, NULL, routine, (void *)philo));
}

void	destroy_t_fork(t_arg *arg)
{
	ssize_t	i;

	i = 0;
	while (i < arg->n_philo)
	{
		pthread_mutex_destroy(&arg->arfork[i].mfork);
		i++;
	}
}

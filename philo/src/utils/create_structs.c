/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_structs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 10:55:03 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/06/11 15:13:19 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_fork	create_t_fork(void)
{
	t_fork	fork;

	fork.fork = true;
	pthread_mutex_init(&fork.mfork, NULL);
	return (fork);
}

t_philo	create_t_philo(int phid, t_param *param)
{
	t_philo	philo;

	philo.nb_ate = 0;
	philo.has_thought = false;
	philo.param = param;
	philo.phid = phid;
	pthread_mutex_init(&philo.time_lock, NULL);
	pthread_mutex_init(&philo.var_lock, NULL);
	if (phid == param->n_philo)
	{
		philo.fork[1] = &param->arfork[0];
		philo.fork[0] = &param->arfork[phid - 1];
	}
	else
	{
		philo.fork[0] = &param->arfork[phid - 1];
		philo.fork[1] = &param->arfork[phid];
	}
	return (philo);
}

void	create_thread(t_philo *philo)
{
	//TODO: check leaks when pthread_create fails
	if (pthread_create(&philo->tid, NULL, routine, (void *)philo) != 0)
		return ;
}

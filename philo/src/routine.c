/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:16:05 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/06/06 14:34:21 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// When a philosopher has finished eating, 
// they put their forks back on the table and start sleeping. 
// Once awake, they start thinking again. 
// The simulation stops when a philosopher dies of starvation.

static void time_to_think(t_philo *phi)
{
	status_message(phi, THINKING);
	usleep(50);
}

static bool	get_forks(t_philo *philo)
{
	bool	left_fork;
	bool	right_fork;

	left_fork = false;
	right_fork = false;
	pthread_mutex_lock(&philo->fork[0].mfork);
	if (philo->fork[0].fork == true)
	{
		pthread_mutex_lock(&philo->param->write_lock);
		printf("\tphilo %3d has taken fork %3d\n", philo->phid, philo->fork[0].ifork);
		pthread_mutex_unlock(&philo->param->write_lock);
		// status_message(philo, FORKING);
		left_fork = true;
		philo->fork[0].fork = false;
	}
	pthread_mutex_unlock(&philo->fork[0].mfork);
	pthread_mutex_lock(&philo->fork[1].mfork);
	if (philo->fork[1].fork == true)
	{
		pthread_mutex_lock(&philo->param->write_lock);
		printf("\tphilo %3d has taken fork %3d\n", philo->phid, philo->fork[1].ifork);
		pthread_mutex_unlock(&philo->param->write_lock);
		// status_message(philo, FORKING);
		philo->fork[1].fork = false;
		right_fork = true;
	}
	pthread_mutex_unlock(&philo->fork[1].mfork);
	if (left_fork == true && right_fork == true)
		return (true);
	else
		return (false);
}

static void	release_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork[0].mfork);
	philo->fork[0].fork = true;
	pthread_mutex_unlock(&philo->fork[0].mfork);
	
	pthread_mutex_lock(&philo->param->write_lock);
	printf("\tphilo %3d has put down fork %3d\n", philo->phid, philo->fork[0].ifork);
	pthread_mutex_unlock(&philo->param->write_lock);
	
	pthread_mutex_lock(&philo->fork[1].mfork);
	philo->fork[1].fork = true;
	pthread_mutex_unlock(&philo->fork[1].mfork);
	
	pthread_mutex_lock(&philo->param->write_lock);
	printf("\tphilo %3d has put down fork %3d\n", philo->phid, philo->fork[1].ifork);
	pthread_mutex_unlock(&philo->param->write_lock);
}

void	*routine(void *arg)
{
	t_philo			*phi;
	time_t			go;
	bool			timeup;

	phi = (t_philo *)arg;
	pthread_mutex_init(&phi->param->write_lock, NULL);
	while (1)
	{
		pthread_mutex_lock(&phi->param->init_lock);
		go = phi->param->start.tv_usec;
		pthread_mutex_unlock(&phi->param->init_lock);
		if (go == 0)
			usleep(10);
		else
			break ;
	}
	if (phi->phid % 2)
		time_to_think(phi);
	while (1)
	{
		if (get_forks(phi))
		{
			status_message(phi, EATING);
			usleep(phi->param->t_to_eat);
			release_forks(phi);
			status_message(phi, SLEEPING);
			usleep(phi->param->t_to_sleep);
		}
		else
			time_to_think(phi);
		pthread_mutex_lock(&phi->param->init_lock);
		timeup = phi->param->died;
		pthread_mutex_unlock(&phi->param->init_lock);
		if (timeup == true)
			break;
		else
			usleep(10);
	}
	return (NULL);
}
	
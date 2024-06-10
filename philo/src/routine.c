/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jauseff <jauseff@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:16:05 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/06/08 02:09:28 by jauseff          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// When a philosopher has finished eating, 
// they put their forks back on the table and start sleeping. 
// Once awake, they start thinking again. 
// The simulation stops when a philosopher dies of starvation.

static void time_to_think(t_philo *phi)
{
	pthread_mutex_lock(&phi->time_lock);
	if (phi->has_thought == false)
		status_message(phi, THINKING, timeup);
	pthread_mutex_unlock(&phi->time_lock);
	usleep(100000);
}


static void	release_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork[0]->mfork);
	philo->fork[0]->fork = true;
	pthread_mutex_unlock(&philo->fork[0]->mfork);

	pthread_mutex_lock(&philo->param->write_lock);
	printf("[%10ld] philo %3d has put down fork %3d\n", get_time_elapsed(philo->param->start), philo->phid, philo->fork[0]->ifork);
	pthread_mutex_unlock(&philo->param->write_lock);

	pthread_mutex_lock(&philo->fork[1]->mfork);
	philo->fork[1]->fork = true;
	pthread_mutex_unlock(&philo->fork[1]->mfork);

	pthread_mutex_lock(&philo->param->write_lock);
	printf("[%10ld] philo %3d has put down fork %3d\n", get_time_elapsed(philo->param->start), philo->phid, philo->fork[1]->ifork);
	pthread_mutex_unlock(&philo->param->write_lock);
}

static void	time_to_eat(t_philo *phi)
{
	pthread_mutex_lock(&phi->time_lock);
	gettimeofday(&phi->last_ate, NULL);
	pthread_mutex_unlock(&phi->time_lock);
	phi->nb_ate += 1;
	pthread_mutex_lock(&phi->time_lock);
	phi->has_thought = false;
	pthread_mutex_unlock(&phi->time_lock);
	status_message(phi, EATING);, timeup
	usleep(phi->param->t_to_eat * 1000);
	release_forks(phi);
}

static bool	get_forks(t_philo *philo)
{
	bool	left_fork;
	bool	right_fork;

	left_fork = false;
	right_fork = false;
	pthread_mutex_lock(&philo->fork[0]->mfork);
	if (philo->fork[0]->fork == true)
	{
		pthread_mutex_lock(&philo->param->write_lock);
		printf("[%10ld] philo %3d has taken fork %3d\n", get_time_elapsed(philo->param->start), philo->phid, philo->fork[0]->ifork);
		pthread_mutex_unlock(&philo->param->write_lock);
		// status_message(philo, FORKIN, timeupG);
		philo->fork[0]->fork = false;
		left_fork = true;
	}
	pthread_mutex_unlock(&philo->fork[0]->mfork);
	pthread_mutex_lock(&philo->fork[1]->mfork);
	if (philo->fork[1]->fork == true)
	{
		pthread_mutex_lock(&philo->param->write_lock);
		printf("[%10ld] philo %3d has taken fork %3d\n", get_time_elapsed(philo->param->start), philo->phid, philo->fork[1]->ifork);
		pthread_mutex_unlock(&philo->param->write_lock);
		// status_message(philo, FORKIN, timeupG);
		philo->fork[1]->fork = false;
		right_fork = true;
	}
	pthread_mutex_unlock(&philo->fork[1]->mfork);
	if (left_fork == true && right_fork == true)
		return (true);
	else
		return (false);
}

void	*routine(void *arg)
{
	t_philo			*phi;
	struct timeval	go;
	bool			timeup;

	phi = (t_philo *)arg;
	pthread_mutex_init(&phi->param->write_lock, NULL);
	while (1)
	{
		pthread_mutex_lock(&phi->param->init_lock);
		go = phi->param->start;
		pthread_mutex_unlock(&phi->param->init_lock);
		if (go.tv_usec == 0)
			usleep(2000);
		else
			break ;
	}
	if (phi->phid % 2)
		time_to_think(phi);
	while (1)
	{
		pthread_mutex_lock(&phi->param->init_lock);
		timeup = phi->param->died;
		pthread_mutex_unlock(&phi->param->init_lock);
		if (timeup == true)
			break;
		if (get_forks(phi))
		{
			time_to_eat(phi);
			status_message(phi, SLEEPING, timeup);
			usleep(phi->param->t_to_sleep * 1000);
		}
		else
		{
			status_message(phi, THINKING, timeup);
			time_to_think(phi);
			pthread_mutex_lock(&phi->time_lock);
			phi->has_thought = true;
			pthread_mutex_unlock(&phi->time_lock);
		}
	}
	return (NULL);
}
	
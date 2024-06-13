/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:16:05 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/06/13 13:49:04 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	time_to_think(t_philo *philo, bool *thought)
{
	if (*thought == false)
		status_message(philo, THINKING);
	*thought = true;
	usleep(50);
}

static void	release_forks(t_philo *philo, int *forks)
{
	pthread_mutex_lock(&philo->fork[0]->mfork);
	philo->fork[0]->fork = true;
	pthread_mutex_unlock(&philo->fork[0]->mfork);
	pthread_mutex_lock(&philo->fork[1]->mfork);
	philo->fork[1]->fork = true;
	pthread_mutex_unlock(&philo->fork[1]->mfork);
	*forks = 0;
}

static void	time_to_eat(t_philo *philo, int *forks, bool *thought)
{
	pthread_mutex_lock(&philo->time_lock);
	gettimeofday(&philo->last_ate, NULL);
	pthread_mutex_unlock(&philo->time_lock);
	status_message(philo, EATING);
	_wait(philo->arg->t_eat);
	release_forks(philo, forks);
	pthread_mutex_lock(&philo->var_lock);
	philo->nb_ate += 1;
	pthread_mutex_unlock(&philo->var_lock);
	*thought = false;
}

static bool	get_forks(t_philo *philo, int *forks)
{
	pthread_mutex_lock(&philo->fork[0]->mfork);
	if (philo->fork[0]->fork == true)
	{
		philo->fork[0]->fork = false;
		pthread_mutex_unlock(&philo->fork[0]->mfork);
		status_message(philo, FORKING);
		*forks += 1;
	}
	else
		pthread_mutex_unlock(&philo->fork[0]->mfork);
	pthread_mutex_lock(&philo->fork[1]->mfork);
	if (philo->fork[1]->fork == true)
	{
		philo->fork[1]->fork = false;
		pthread_mutex_unlock(&philo->fork[1]->mfork);
		status_message(philo, FORKING);
		*forks += 1;
	}
	else
		pthread_mutex_unlock(&philo->fork[1]->mfork);
	if (*forks == 2)
		return (true);
	return (false);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	int		forks;
	bool	thought;

	philo = (t_philo *)arg;
	forks = 0;
	thought = false;
	wait_to_go(philo);
	if (philo->phid % 2)
		_wait(philo->arg->t_eat / 2);
	while (alive(philo))
	{
		if (get_forks(philo, &forks))
		{
			time_to_eat(philo, &forks, &thought);
			status_message(philo, SLEEPING);
			_wait(philo->arg->t_sleep);
		}
		else
			time_to_think(philo, &thought);
	}
	return (NULL);
}

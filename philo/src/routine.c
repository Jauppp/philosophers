/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:16:05 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/06/11 15:35:05 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	time_to_think(t_philo *phi, bool *thought)
{
	if (*thought == false)
		status_message(phi, THINKING);
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

static void	time_to_eat(t_philo *phi, int *forks, bool *thought)
{
	pthread_mutex_lock(&phi->var_lock);
	phi->nb_ate += 1;
	pthread_mutex_unlock(&phi->var_lock);
	*thought = false;
	pthread_mutex_lock(&phi->time_lock);
	gettimeofday(&phi->last_ate, NULL);
	pthread_mutex_unlock(&phi->time_lock);
	status_message(phi, EATING);
	_wait(phi->param->t_to_eat);
	release_forks(phi, forks);
}

static bool	get_forks(t_philo *philo, int *forks)
{
	pthread_mutex_lock(&philo->fork[0]->mfork);
	if (philo->fork[0]->fork == true)
	{
		*forks += 1;
		philo->fork[0]->fork = false;
		pthread_mutex_unlock(&philo->fork[0]->mfork);
		status_message(philo, FORKING);
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
	t_philo	*phi;
	int		forks;
	bool	thought;

	phi = (t_philo *)arg;
	forks = 0;
	thought = false;
	wait_to_go(phi);
	if (phi->phid % 2)
		usleep((phi->param->t_to_eat / 2) * 1000);
	while (alive(phi))
	{
		if (get_forks(phi, &forks))
		{
			time_to_eat(phi, &forks, &thought);
			status_message(phi, SLEEPING);
			_wait(phi->param->t_to_sleep);
		}
		else
			time_to_think(phi, &thought);
	}
	return (NULL);
}

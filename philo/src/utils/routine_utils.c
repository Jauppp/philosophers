/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:50:19 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/06/12 15:19:53 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_starting_time(t_philo	*pharr, t_arg *arg)
{
	struct timeval	go_time;
	ssize_t			i;

	gettimeofday(&go_time, NULL);
	pthread_mutex_lock(&arg->init_lock);
	arg->start = go_time;
	pthread_mutex_unlock(&arg->init_lock);
	i = 0;
	while (i < arg->n_philo)
	{
		pthread_mutex_lock(&pharr[i].time_lock);
		pharr[i].last_ate = go_time;
		pthread_mutex_unlock(&pharr[i].time_lock);
		i++;
	}
}

void	wait_to_go(t_philo	*philo)
{
	struct timeval	go_time;

	while (1)
	{
		pthread_mutex_lock(&philo->arg->init_lock);
		go_time = philo->arg->start;
		pthread_mutex_unlock(&philo->arg->init_lock);
		if (go_time.tv_usec == 0)
			usleep(20);
		else
			break ;
	}
	return ;
}

bool	alive(t_philo	*philo)
{
	bool	timeup;

	pthread_mutex_lock(&philo->arg->init_lock);
	timeup = philo->arg->died;
	pthread_mutex_unlock(&philo->arg->init_lock);
	if (timeup == true)
		return (false);
	else
		return (true);
}

bool	all_fed(t_philo	*pharr)
{
	size_t	i;
	size_t	n_phi;
	bool	all_fed;

	i = -1;
	n_phi = pharr->arg->n_philo;
	all_fed = false;
	while (++i < n_phi)
	{
		pthread_mutex_lock(&pharr[i].var_lock);
		if (pharr[i].nb_ate >= pharr[i].arg->max_meals)
		{
			pthread_mutex_unlock(&pharr[i].var_lock);
			all_fed = true;
		}
		else
		{
			pthread_mutex_unlock(&pharr[i].var_lock);
			all_fed = false;
			break ;
		}
	}
	if (all_fed == true)
		return (true);
	return (false);
}

bool	meal_limit(t_philo *pharr)
{
	if (pharr->arg->max_meals != -1)
		return (true);
	return (false);
}

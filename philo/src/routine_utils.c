/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:50:19 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/06/11 15:28:06 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_starting_time(t_philo	*philarray, t_param *param)
{
	struct timeval	go_time;
	ssize_t			i;

	gettimeofday(&go_time, NULL);
	pthread_mutex_lock(&param->init_lock);
	param->start = go_time;
	pthread_mutex_unlock(&param->init_lock);
	i = 0;
	while (i < param->n_philo)
	{
		pthread_mutex_lock(&philarray[i].time_lock);
		philarray[i].last_ate = go_time;
		pthread_mutex_unlock(&philarray[i].time_lock);
		i++;
	}
}

void	wait_to_go(t_philo	*philo)
{
	struct timeval	go_time;

	while (1)
	{
		pthread_mutex_lock(&philo->param->init_lock);
		go_time = philo->param->start;
		pthread_mutex_unlock(&philo->param->init_lock);
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

	pthread_mutex_lock(&philo->param->init_lock);
	timeup = philo->param->died;
	pthread_mutex_unlock(&philo->param->init_lock);
	if (timeup == true)
		return (false);
	else
		return (true);
}

bool	all_fed(t_philo	*philarray)
{
	size_t	i;
	size_t	n_phi;
	bool	all_fed;

	i = 0;
	n_phi = philarray->param->n_philo;
	all_fed = false;
	while (i < n_phi)
	{
		pthread_mutex_lock(&philarray[i].var_lock);
		if (philarray[i].nb_ate == philarray[i].param->n_must_eat)
		{
			pthread_mutex_unlock(&philarray[i].var_lock);
			all_fed = true;
		}
		else
		{
			pthread_mutex_unlock(&philarray[i].var_lock);
			all_fed = false;
		}
		i++;
	}
	if (all_fed == true)
		return (true);
	return (false);
}

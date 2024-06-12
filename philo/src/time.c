/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:25:03 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/06/12 15:00:03 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	get_time_elapsed(struct timeval start)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (((tv.tv_usec - start.tv_usec) / 1000) + \
	((tv.tv_sec - start.tv_sec) * 1000));
}

void	_wait(time_t time)
{
	time_t			elapsed;
	time_t			to_wait;
	struct timeval	start_wait;

	gettimeofday(&start_wait, NULL);
	to_wait = (time * 1000) * 0.80;
	usleep(to_wait);
	elapsed = get_time_elapsed(start_wait);
	while (elapsed < time)
	{
		usleep(50);
		elapsed = get_time_elapsed(start_wait);
	}
}

time_t	update_time(t_philo *philo)
{
	time_t	time;

	pthread_mutex_lock(&philo->time_lock);
	time = get_time_elapsed(philo->last_ate);
	pthread_mutex_unlock(&philo->time_lock);
	return (time);
}

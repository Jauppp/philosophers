/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:25:03 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/06/06 13:52:06 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// get elapsed time from start in milliseconds
time_t	get_time_elapsed(struct timeval start)
{
	struct timeval	tv;
	
	gettimeofday(&tv, NULL);
	return (((tv.tv_usec - start.tv_usec) / 1000) + \
	((tv.tv_sec - start.tv_sec) * 1000));
}
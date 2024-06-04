/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:16:05 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/06/04 14:28:00 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo		*phi;
	bool		end;
	
	phi = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&phi->param->init_lock);
		end = phi->param->end;
		pthread_mutex_unlock(&phi->param->init_lock);
		if (end != true)
			usleep(10);
		else 
			break ;
	}
	dphi(*phi);
	// fprintf(stderr, "🍴 I am philo %3d, TID : %10ld\n", phi->phid, phi->tid);
	return (NULL);
}
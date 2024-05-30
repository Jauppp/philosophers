/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:15:03 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/05/30 15:09:41 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Your(s) program(s) should take the following arguments:
	// - number_of_philosophers 
	// - time_to_die 
	// - time_to_eat 
	// - time_to_sleep
	// - [number_of_times_each_philosopher_must_eat

int	init_params(t_param	*params, char **args)
{
	params->nb_of_philo = ft_atoi(args[1]);
	if (params->nb_of_philo < 1)
		return (ERROR);
	params->time_to_die = ft_atoi(args[2]);
	if (params->time_to_die < 1)
		return (ERROR);
	params->time_to_eat = ft_atoi(args[3]);
	if (params->time_to_eat < 1)
		return (ERROR);
	params->time_to_sleep = ft_atoi(args[4]);
	if (params->time_to_sleep < 1)
		return (ERROR);
	if (args[5])
	{
		params->nb_must_eat = ft_atoi(args[5]);
		if (params->time_to_sleep < 1)
			return (ERROR);
	}
	else
		params->nb_must_eat = -1;
	return (SUCESS);
}


pthread_t create_philo(void)
{
	pthread_t	philo;

	if (pthread_create(&philo, NULL, routine, NULL) == -1)
		return (1);
	return (philo);
}


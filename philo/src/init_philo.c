/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:15:03 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/05/31 18:11:12 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Your(s) program(s) should take the following arguments:
	// - number_of_philosophers 
	// - time_to_die 
	// - time_to_eat 
	// - time_to_sleep
	// - [number_of_times_each_philosopher_must_eat

int isnotdigit(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
		{
			return (ERROR);
		}
		i++;
	}
	return (SUCESS);
}

int	isdigit_param(char **args)
{
	size_t	i;

	i = 1;
	if (!args || !args[i])
		return (ERROR);
	while (args[i])
	{
		if (isnotdigit(args[i]) == ERROR)
			return (ERROR);
		i++;
	}
	return (SUCESS);
}

int	init_params(t_param	*param, char **args)
{
	if (isdigit_param(args) == ERROR)
		return (derr("Invalid argument: ", "alpha character detected"));
	param->nb_of_philo = ft_atoi(args[1]);
	if (param->nb_of_philo < 1)
		return (derr("Invalid argument: ", args[1]));
	param->time_to_die = ft_atoi(args[2]);
	if (param->time_to_die < 1)
		return (derr("Invalid argument: ", args[2]));
	param->time_to_eat = ft_atoi(args[3]);
	if (param->time_to_eat < 1)
		return (derr("Invalid argument: ", args[3]));
	param->time_to_sleep = ft_atoi(args[4]);
	if (param->time_to_sleep < 1)
		return (derr("Invalid argument: ", args[4]));
	if (args[5])
	{
		param->nb_must_eat = ft_atoi(args[5]);
		if (param->time_to_sleep < 1)
			return (derr("Invalid argument: ", args[5]));
	}
	else
		param->nb_must_eat = -1;
	dpm(*param);
	return (SUCESS);
}


pthread_t create_philo(void)
{
	pthread_t	philo;

	if (pthread_create(&philo, NULL, routine, NULL) == -1)
		return (1);
	return (philo);
}


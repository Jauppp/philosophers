/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:15:03 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/06/03 18:06:05 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Your(s) program(s) should take the following arguments:
	// - number_of_philosophers 
	// - time_to_die 
	// - time_to_eat 
	// - time_to_sleep
	// - [number_of_times_each_philosopher_must_eat

int	init_params(t_param	*param, char **args)
{
	if (isdigit_param(args) == ERROR)
		return (ERROR);
	param->n_philo = ft_atoi(args[1]);
	if (param->n_philo < 1)
		return (derr("Invalid argument: ", args[1]));
	param->t_to_die = ft_atoi(args[2]);
	if (param->t_to_die < 1)
		return (derr("Invalid argument: ", args[2]));
	param->t_to_eat = ft_atoi(args[3]);
	if (param->t_to_eat < 1)
		return (derr("Invalid argument: ", args[3]));
	param->t_to_sleep = ft_atoi(args[4]);
	if (param->t_to_sleep < 1)
		return (derr("Invalid argument: ", args[4]));
	if (args[5])
	{
		param->n_must_eat = ft_atoi(args[5]);
		if (param->t_to_sleep < 1)
			return (derr("Invalid argument: ", args[5]));
	}
	else
		param->n_must_eat = -1;
	dpm(*param);
	return (SUCCESS);
}

static t_philo	*create_t_philo(int ph_id)
{
	t_philo	*philo;
	
	philo = malloc(1 * sizeof(t_philo));
	if (!philo)
		return(NULL);
	philo->ph_id = ph_id;
	return (philo);
}

static pthread_t create_thread(t_philo *phi)
{
	//TODO: check leaks when pthread_create fails
	pthread_t	philo;

	if (pthread_create(&philo, NULL, routine, phi) == -1)
		return (ERROR);
	return (philo);
}

int	init_philo(t_table *table)
{
	ssize_t	i;

	i = 0;
	table->philos = malloc((table->param.n_philo + 1) * sizeof (t_philo **));
	if (!table->philos)
		return (derr("Memory allocation issue", NULL));
	table->philos[table->param.n_philo] = NULL;
	while (i < table->param.n_philo)
	{
		table->philos[i] = create_t_philo(i);
		table->philos[i]->t_id = create_thread(table->philos[i]);
		if (table->philos[i]->t_id == ERROR)
			return (ERROR);
		i++;
	}
	// i = 0;
	// while(table->philos[i])
	// 	fprintf(stderr, "🍴 I am philo : %3d\n", table->philos[i++]->ph_id);
	return (SUCCESS);
}



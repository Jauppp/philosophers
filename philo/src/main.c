/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:16:29 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/06/03 17:46:46 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int join_phi(t_table *table)
{
	ssize_t		i;
	int	err;

	i = 0;
	while (i < table->param.n_philo)
	{
		err = pthread_join(table->philos[i++]->t_id, NULL);
		if (err != 0)
		{
			printf("%d\n", err);
			return (derr("Error joining threads: ", NULL));
		}
	}
	i = 0;
	while (table->philos[i])
		free(table->philos[i++]);
	free(table->philos);
	return (SUCCESS);
}

int	main(int argc, char *argv[])
{
	t_table	table;

	if (argc > 6 || argc < 5)
		return (derr(INPUT_ERROR, NULL));
	if (init_params(&table.param, argv) == ERROR)
		return (ERROR);
	if (init_philo(&table) == ERROR)
	{
		join_phi(&table);
		return(ERROR);
	}
	join_phi(&table);
	return (SUCCESS);
}

	// pthread_t 	phi;
	// pthread_t	*a_philo;
	// size_t	i;
	// i = 0;
	// while (i < 5)
	// {
	// 	a_philo[i] = 0;
	// 	i++;
	// }
	// i = 0;
	// while (i < 5)
	// {
	// 	phi = create_philo();
	// 	if (phi == 1)
	// 		return (ERROR);
	// 	a_philo[i] = phi;
	// 	i++;
	// }
	// i = 0;
	// while (i < 5)
	// {
	// 	pthread_join(a_philo[i], NULL);
	// 	i++;
	// }

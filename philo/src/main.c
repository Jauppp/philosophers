/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:16:29 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/05/31 17:44:55 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_param	param;

	if (argc > 6 || argc < 5)
		return (derr("Please enter in milliseconds :\n - number_of_philosophers\n - time_to_die\n - time_to_eat\n - time_to_sleep", NULL));
	if (init_params(&param, argv) == ERROR)
		return (ERROR);
	// dpm(param);
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
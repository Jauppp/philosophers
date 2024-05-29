/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:16:29 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/05/29 17:40:54 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*routine(void *arg)
{

	pthread_t	tid;

	(void)arg;
	tid = pthread_self();
	fprintf(stderr, "🍴 I am tread 🍴 %9lu\n", tid);
	return (NULL);
}

pthread_t create_philo(void)
{
	pthread_t	philo;

	if (pthread_create(&philo, NULL, routine, NULL) == -1)
		return (1);
	return (philo);
}

int	main(void)
{
	pthread_t 	phi;
	pthread_t	a_philo[5];
	size_t	i;

	i = 0;
	a_philo[4] = 0;
	while (i < 5)
	{
		a_philo[i] = 0;
		i++;
	}
	i = 0;
	while (i < 5)
	{
		phi = create_philo();
		if (phi == 1)
			return (1);
		a_philo[i] = phi;
		i++;
	}
	i = 0;
	while (i < 5)
	{
		pthread_join(a_philo[i], NULL);
		i++;
	}
}


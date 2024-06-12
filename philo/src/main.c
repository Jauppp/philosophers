/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:16:29 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/06/12 17:02:43 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	join_phi(t_philo *pharr)
{
	ssize_t	i;
	int		err;

	i = 0;
	if (!pharr)
		return (SUCCESS);
	while (i < pharr->arg->n_philo)
	{
		err = pthread_join(pharr[i++].tid, NULL);
		if (err != 0)
		{
			printf("%d\n", err);
			return (derr("Error joining threads: ", NULL));
		}
	}
	destroy_t_fork(pharr->arg);
	pthread_mutex_destroy(&pharr->arg->init_lock);
	pthread_mutex_destroy(&pharr->arg->write_lock);
	free(pharr->arg->arfork);
	free(pharr);
	return (SUCCESS);
}

void	time_is_up(t_philo	*pharr)
{
	time_t	time;
	size_t	n_phi;
	size_t	i;
	bool	fed;

	i = 0;
	n_phi = pharr->arg->n_philo;
	fed = meal_limit(pharr);
	while (1)
	{
		time = update_time(pharr + i);
		if (time >= pharr[i].arg->t_die || (all_fed(pharr) && fed == true))
		{
			pthread_mutex_lock(&pharr[i].arg->init_lock);
			pharr[i].arg->died = true;
			pthread_mutex_unlock(&pharr[i].arg->init_lock);
			if (all_fed(pharr) == 1 && fed == true)
				return ;
			status_message(pharr + i, DEAD);
			return ;
		}
		i = (i + 1) % n_phi;
		usleep(10);
	}
}

int	main(int argc, char *argv[])
{
	t_arg		arg;
	t_philo		*pharr;

	pharr = NULL;
	if (argc > 6 || argc < 5)
		return (derr(INPUT_ERROR, NULL));
	if (init_args(&arg, argv) == ERROR)
		return (ERROR);
	pharr = malloc((arg.n_philo + 1) * sizeof (t_philo));
	if (!pharr)
		return (derr("Memory allocation issue", NULL));
	memset((t_philo *)pharr, 0, sizeof(t_philo));
	if (init_philo(&arg, pharr) == ERROR)
	{
		join_phi(pharr);
		return (ERROR);
	}
	time_is_up(pharr);
	join_phi(pharr);
	return (SUCCESS);
}

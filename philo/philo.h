/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:17:05 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/05/30 17:41:19 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <limits.h>
# include <unistd.h>

# define ERROR 1
# define SUCESS 0

typedef struct s_param {
	size_t	nb_of_philo;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	size_t	nb_must_eat;
} t_param;

// . -------------------------

/* routine.c */
void	*routine(void *arg);

/* init_philo.c */
int	init_params(t_param	*params, char **args);
pthread_t create_philo(void);

/* utils.c */
int	derr(char *err);

/* ft_atoi.c */
int	ft_atoi(char *nptr);

// display -------------------

/* display.c */
ssize_t	ft_putendl_fd(char *s, int fd);
void	dpm(t_param param);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:17:05 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/05/31 17:50:56 by cdomet-d         ###   ########lyon.fr   */
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
	ssize_t	nb_of_philo;
	ssize_t	time_to_die;
	ssize_t	time_to_eat;
	ssize_t	time_to_sleep;
	ssize_t	nb_must_eat;
} t_param;

// . -------------------------

/* routine.c */
void	*routine(void *arg);

/* init_philo.c */
int	init_params(t_param	*params, char **args);
pthread_t create_philo(void);

/* utils.c */
int	derr(char *err, char *param);

/* ft_atoi.c */
int	ft_atoi(char *nptr);

// display -------------------

/* display.c */
ssize_t	ft_putendl_fd(char *s, int fd);
ssize_t	ft_putl_fd(char *s, int fd);
void	dpm(t_param param);

#endif
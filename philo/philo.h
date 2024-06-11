/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:17:05 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/06/11 15:31:10 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/time.h>
# include <string.h>

# define ERROR 1
# define SUCCESS 0
# define INPUT_ERROR "Please enter in milliseconds :\n - \
number_of_philosophers\n - time_to_die\n - time_to_eat\n - time_to_sleep"

# define EATING "is eating"
# define FORKING "has taken a fork"
# define THINKING "is thinking"
# define SLEEPING "is sleeping"
# define DEAD "died"

typedef struct s_fork
{
	bool			fork;
	int				ifork;
	pthread_mutex_t	mfork;
}	t_fork;

typedef struct s_param
{
	bool			died;
	struct timeval	start;
	pthread_mutex_t	init_lock;
	pthread_mutex_t	write_lock;
	ssize_t			n_must_eat;
	ssize_t			n_philo;
	time_t			t_to_die;
	time_t			t_to_eat;
	time_t			t_to_sleep;
	t_fork			*arfork;
}	t_param;

typedef struct s_philo
{
	bool			has_thought;
	int				phid;
	pthread_mutex_t	time_lock;
	pthread_mutex_t	var_lock;
	pthread_t		tid;
	ssize_t			nb_ate;
	struct timeval	last_ate;
	t_fork			*fork[2];
	t_param			*param;
}	t_philo;

// utils ---------------------

/* error_management.c */
int		derr(char *err, char *param);

/* ft_atoi.c */
int		ft_atoi(char *nptr);

/* parsing.c */
int		isnotdigit(char *str);
int		isdigit_param(char **args);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

/* create_structs.c */
t_fork	create_t_fork(void);
t_philo	create_t_philo(int phid, t_param *param);
void	create_thread(t_philo *philo);

/* display.c */
ssize_t	ft_putendl_fd(char *s, int fd);
ssize_t	status_message(t_philo *philo, char *status);
ssize_t	ft_putl_fd(char *s, int fd);

// src -----------------------

/* initialisation.c */
int		init_params(t_param	*param, char **args);
int		init_philo(t_param *param, t_philo *philarray);

/* time.c */
time_t	get_time_elapsed(struct timeval start);
void	_wait(time_t time);

/* main.c */
int		join_phi(t_philo *philo);
void	time_is_up(t_philo	*philarray);

/* routine.c */
void	*routine(void *arg);

/* routine_utils.c */
void	wait_to_go(t_philo	*philo);
bool	alive(t_philo	*philo);
void	get_starting_time(t_philo	*philarray, t_param *param);
bool	all_fed(t_philo	*philarray);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jauseff <jauseff@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:41:42 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/06/08 02:11:11 by jauseff          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s || !*s)
		return (0);
	while (s && s[i])
		i++;
	return (i);
}

ssize_t	ft_putendl_fd(char *s, int fd)
{
	ssize_t	len;

	len = write(fd, s, ft_strlen(s));
	if (len == -1)
		return (len);
	len += write(fd, "\n", 1);
	if (len == -1)
		return (len);
	return (len);
}

ssize_t	status_message(t_philo *philo, char *status, bool timeup)
{
	ssize_t			r_value;

	if (timeup)
		return (1);
	pthread_mutex_lock(&philo->param->write_lock);
	r_value = printf("[%10ld] philo %3d %s\n", \
	get_time_elapsed(philo->param->start),philo->phid, status);
	pthread_mutex_unlock(&philo->param->write_lock);
	if (r_value == -1)
		return (-1);
	else
		return (SUCCESS);

}

ssize_t	ft_putl_fd(char *s, int fd)
{
	ssize_t	len;

	len = write(fd, s, ft_strlen(s));
	if (len == -1)
		return (len);
	return (len);
}

void	dpm(t_param param)
{
	printf("%.35s\n", "-- PARAMS --------------------------------------------");
	printf("%.35s\t | %10ld | \n", "number of philo", param.n_philo);
	printf("%.35s\t | %10ld | ms\n", "time to die", param.t_to_die);
	printf("%.35s\t | %10ld | ms\n", "time to eat", param.t_to_eat);
	printf("%.35s\t | %10ld | ms\n", "time to sleep", param.t_to_sleep);
	if (param.n_must_eat != -1)
		printf("%.35s\t | %4ld | ms\n", "must eat", param.n_must_eat);
	printf("%.35s\n", "------------------------------------------------------");
}

/*void	dphi(t_philo phi)
{
	fprintf(stderr, "| I am philo %.3d 🍴 \t\t\t\t|\n\
| My left fork is at %d - my right fork is at %d  |\n\
| I last ate %.3ld ms ago, it was my %.3ldth meal\t|\n\n", phi.phid, \
phi.fork[0].ifork, phi.fork[1].ifork, phi.last_ate, phi.nb_ate);	
	fprintf(stderr, "| I am philo %.3d 🍴 \t\t\t\t|\n", phi.phid);
}*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:41:42 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/06/12 17:05:37 by cdomet-d         ###   ########lyon.fr   */
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

ssize_t	ft_putl_fd(char *s, int fd)
{
	ssize_t	len;

	len = write(fd, s, ft_strlen(s));
	if (len == -1)
		return (len);
	return (len);
}

ssize_t	status_message(t_philo *philo, char *status)
{
	ssize_t	r_value;

	pthread_mutex_lock(&philo->arg->write_lock);
	if (alive(philo) == false && ft_strncmp(status, "died", 4) != 0)
	{
		pthread_mutex_unlock(&philo->arg->write_lock);
		return (1);
	}
	r_value = printf("%-5ld %-3d %s\n", \
	get_time_elapsed(philo->arg->start), philo->phid, status);
	pthread_mutex_unlock(&philo->arg->write_lock);
	if (r_value == -1)
		return (-1);
	else
		return (SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:41:42 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/05/31 17:50:07 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

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

void	dpm(t_param param)
{
	printf("%.15s [%ld]\n", "number of philosophers",  param.nb_of_philo);
	printf("%.15s [%ld]\n", "time to die", param.time_to_die);
	printf("%.15s [%ld]\n", "time to eat", param.time_to_eat);
	printf("%.15s [%ld]\n", "time to sleep", param.time_to_sleep);
	if (param.nb_must_eat != 0)
		printf("%.15s [%ld]\n", "number of time\na philosopher must eat", \
		param.nb_must_eat);
}
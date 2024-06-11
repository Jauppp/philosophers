/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 12:57:13 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/06/11 11:39:49 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	isnotdigit(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
		{
			return (ERROR);
		}
		i++;
	}
	return (SUCCESS);
}

int	isdigit_param(char **args)
{
	size_t	i;

	i = 1;
	if (!args || !args[i])
		return (ERROR);
	while (args[i])
	{
		if (isnotdigit(args[i]) == ERROR)
			return (derr("Alpha character in", args[i]));
		i++;
	}
	return (SUCCESS);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!n)
		return (0);
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

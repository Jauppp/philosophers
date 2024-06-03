/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 12:57:13 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/06/03 14:35:59 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int isnotdigit(char *str)
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
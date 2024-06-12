/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:54:34 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/06/12 15:04:35 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	derr(char *err, char *arg)
{
	if (err && arg)
	{
		ft_putl_fd(err, STDERR_FILENO);
		ft_putendl_fd(arg, STDERR_FILENO);
	}
	else if (err)
		ft_putendl_fd(err, STDERR_FILENO);
	else if (arg)
		ft_putendl_fd(arg, STDERR_FILENO);
	return (ERROR);
}

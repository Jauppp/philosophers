/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:54:34 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/05/31 17:51:38 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	derr(char *err, char *param)
{
	if (err && param)
	{
		ft_putl_fd(err, STDERR_FILENO);
		ft_putendl_fd(param, STDERR_FILENO);
	}
	else if (err)
		ft_putendl_fd(err, STDERR_FILENO);
	else if (param)
		ft_putendl_fd(param, STDERR_FILENO);
	return (ERROR);
}
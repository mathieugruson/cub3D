/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 18:50:12 by mgruson           #+#    #+#             */
/*   Updated: 2023/01/26 20:25:00 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_fd_error(void)
{
	ft_printf("Error\n%s\n", strerror(errno));
	exit(EXIT_FAILURE);
}

void	ft_str_error(void)
{
	ft_printf("Error\nEmpty map file\n");
	exit(EXIT_FAILURE);
}

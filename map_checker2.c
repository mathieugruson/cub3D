/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 19:11:00 by mgruson           #+#    #+#             */
/*   Updated: 2023/01/26 23:18:40 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_invasion_checker_condition(t_v *v, int x, int y, char c)
{
	if (x - 1 >= 0 && v->m.map[y][x - 1] != '1' && v->m.map[y][x - 1] != c \
	&& v->m.map[y][x - 1] != ' ' && v->m.map[y][x - 1] != 'n')
		return (1);
	if (v->m.map[y][x + 1])
	{
		if (v->m.map[y][x + 1] != '1' && v->m.map[y][x + 1] != c \
		&& v->m.map[y][x + 1] != ' ' && v->m.map[y][x + 1] != '\n')
			return (1);
	}
	if (y - 1 > 0 && (int)ft_strlen(v->m.map[y - 1]) >= x)
	{
		if (v->m.map[y - 1][x] && v->m.map[y - 1][x] != '1' \
		&& v->m.map[y - 1][x] != c && v->m.map[y - 1][x] != ' ' \
		&& v->m.map[y - 1][x] != '\n')
			return (1);
	}
	if (v->m.map[y + 1] && (int)ft_strlen(v->m.map[y + 1]) >= x)
	{
		if (v->m.map[y + 1][x] && v->m.map[y + 1][x] != '1' \
		&& v->m.map[y + 1][x] != c && v->m.map[y + 1][x] != ' ' \
		&& v->m.map[y + 1][x] != '\n')
			return (1);
	}
	return (0);
}

int	ft_invasion_checker(t_v *v, char c)
{
	int	x;
	int	y;

	y = 0;
	while (v->m.map[y])
	{
		x = 0;
		while (v->m.map[y][x])
		{
			if (v->m.map[y][x] == c)
			{
				if (x == 0)
					return (0);
				if (ft_invasion_checker_condition(v, x, y, c) == 1)
					return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

void	ft_invasion_loop_checker(t_v *v, int x, int y, char c)
{
	if (x - 1 >= 0 && v->m.map[y][x - 1] != '1' && v->m.map[y][x - 1] != c \
	&& v->m.map[y][x - 1] != ' ')
		ft_invasion_propagation(x, y, v, c);
	if (v->m.map[y][x + 1])
	{
		if (v->m.map[y][x + 1] != '1' && v->m.map[y][x + 1] != c \
		&& v->m.map[y][x + 1] != ' ')
			ft_invasion_propagation(x, y, v, c);
	}
	if (y - 1 >= 0 && (int)ft_strlen(v->m.map[y - 1]) >= x)
	{
		if (v->m.map[y - 1][x] != '1' && v->m.map[y - 1][x] != c \
		&& v->m.map[y - 1][x] != ' ' && v->m.map[y - 1][x])
			ft_invasion_propagation(x, y, v, c);
	}
	if (v->m.map[y + 1] && (int)ft_strlen(v->m.map[y + 1]) >= x)
	{
		if (v->m.map[y + 1][x] != '1' && v->m.map[y + 1][x] != c \
		&& v->m.map[y + 1][x] != ' ' && v->m.map[y + 1][x])
			ft_invasion_propagation(x, y, v, c);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_attack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 18:11:11 by chillion          #+#    #+#             */
/*   Updated: 2023/01/26 19:29:29 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_west_offensive(int x, int y, t_v *v, char c)
{
	int	tx;
	int	ty;

	ty = y;
	tx = x;
	while (tx >= 0 && v->m.map[ty][tx] && v->m.map[ty][tx] != '1'\
	&& v->m.map[ty][tx] != ' ' && v->m.map[ty][tx] != '\n')
	{
		propagate_player(v, tx, ty, c);
		if (ty - 1 > 0 && (int)ft_strlen(v->m.map[ty - 1]) >= tx)
		{
			if (v->m.map[ty - 1][tx] != '\0' \
			&& v->m.map[ty - 1][tx] != '1' && v->m.map[ty - 1][tx] != c \
			&& v->m.map[ty - 1][tx] != ' ' && v->m.map[ty - 1][tx] != '\n')
				v->m.map[ty - 1][tx] = c;
		}
		if (v->m.map[ty + 1] && (int)ft_strlen(v->m.map[ty + 1]) >= tx + 1)
		{
			if (v->m.map[ty + 1][tx] && v->m.map[ty + 1][tx] != '1' \
			&& v->m.map[ty + 1][tx] != c && v->m.map[ty + 1][tx] != ' ' \
			&& v->m.map[ty + 1][tx] != '\n')
				v->m.map[ty + 1][tx] = c;
		}
		tx--;
	}
}

void	ft_north_offensive(int x, int y, t_v *v, char c)
{
	int	tx;
	int	ty;

	ty = y;
	tx = x;
	while (v->m.map[ty][tx] && v->m.map[ty][tx] != '1' \
	&& v->m.map[ty][tx] != ' ' && v->m.map[ty][tx] != '\n')
	{
		propagate_player(v, tx, ty, c);
		if (tx - 1 >= 0)
		{
			if (v->m.map[ty][tx - 1] != '1' && v->m.map[ty][tx - 1] != c \
			&& v->m.map[ty][tx - 1] != ' ' && v->m.map[ty][tx - 1] != '\n')
				v->m.map[ty][tx - 1] = c;
		}
		if (v->m.map[ty][tx + 1] && v->m.map[ty][tx + 1] != '1' \
		&& v->m.map[ty][tx + 1] != c && v->m.map[ty][tx + 1] != ' ' \
		&& v->m.map[ty][tx + 1] != '\n')
			v->m.map[ty][tx + 1] = c;
		if (ty - 1 > 0 && (int)ft_strlen(v->m.map[ty - 1]) < tx + 1)
			break ;
		ty--;
	}
}

void	ft_east_offensive(int x, int y, t_v *v, char c)
{
	int	tx;
	int	ty;

	ty = y;
	tx = x;
	while (v->m.map[ty][tx] && v->m.map[ty][tx] != '1' \
	&& v->m.map[ty][tx] != ' ' && v->m.map[ty][tx] != '\n')
	{
		propagate_player(v, tx, ty, c);
		if (ty - 1 > 0 && (int)ft_strlen(v->m.map[ty - 1]) >= tx)
		{
			if (v->m.map[ty - 1][tx] && v->m.map[ty - 1][tx] != '1' \
			&& v->m.map[ty - 1][tx] != c && v->m.map[ty - 1][tx] != ' ' \
			&& v->m.map[ty - 1][tx] != '\n')
				v->m.map[ty - 1][tx] = c;
		}
		if (v->m.map[ty + 1] && (int)ft_strlen(v->m.map[ty + 1]) >= tx)
		{
			if (v->m.map[ty + 1][tx] && v->m.map[ty + 1][tx] != '1' \
			&& v->m.map[ty + 1][tx] != c && v->m.map[ty + 1][tx] != ' ' \
			&& v->m.map[ty + 1][tx] != '\n')
				v->m.map[ty + 1][tx] = c;
		}
		tx++;
	}
}

void	ft_south_offensive(int x, int y, t_v *v, char c)
{
	int	tx;
	int	ty;

	ty = y;
	tx = x;
	while (v->m.map[ty][tx] && v->m.map[ty][tx] != '1' \
	&& v->m.map[ty][tx] != ' ' && v->m.map[ty][tx] != '\n')
	{
		propagate_player(v, tx, ty, c);
		if (tx - 1 >= 0)
		{
			if (v->m.map[ty][tx - 1] != '1' \
			&& v->m.map[ty][tx - 1] != c && v->m.map[ty][tx - 1] != ' ')
				v->m.map[ty][tx - 1] = c;
		}
		if (v->m.map[ty][tx + 1] && v->m.map[ty][tx + 1] != '1' \
		&& v->m.map[ty][tx + 1] != c && v->m.map[ty][tx + 1] != ' ' \
		&& v->m.map[ty][tx + 1] != '\n')
			v->m.map[ty][tx + 1] = c;
		if ((ft_tablen(v->m.map) < ty + 1) || \
		(int)ft_strlen(v->m.map[ty + 1]) < tx + 1)
			break ;
		ty++;
	}
}

int	ft_invasion_propagation(int x, int y, t_v *v, char c)
{
	ft_west_offensive(x, y, v, c);
	ft_north_offensive(x, y, v, c);
	ft_east_offensive(x, y, v, c);
	ft_south_offensive(x, y, v, c);
	return (0);
}

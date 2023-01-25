/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_attack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chillion <chillion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 18:11:11 by chillion          #+#    #+#             */
/*   Updated: 2023/01/25 17:50:35 by chillion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_west_offensive(int x, int y, t_v *v, char c)
{
	int	tmpx;
	int	tmpy;

	tmpy = y;
	tmpx = x;
	while (v->m.map[tmpy][tmpx] && v->m.map[tmpy][tmpx] != '1'\
	&& v->m.map[tmpy][tmpx] != ' ' && v->m.map[tmpy][tmpx] != '\n')
	{
		if (v->m.map[tmpy][tmpx] != '1' && v->m.map[tmpy][tmpx] != c \
		&& v->m.map[tmpy][tmpx] != ' '&& v->m.map[tmpy][tmpx] != '\n')
			v->m.map[tmpy][tmpx] = c;
		if ((int)ft_strlen(v->m.map[tmpy - 1]) >= tmpx)
		{
			if (v->m.map[tmpy - 1][tmpx] != '1' && v->m.map[tmpy - 1][tmpx] != c \
			&& v->m.map[tmpy - 1][tmpx] != ' ' && v->m.map[tmpy - 1][tmpx] != '\n')
				v->m.map[tmpy - 1][tmpx] = c;
		}
		if ((int)ft_strlen(v->m.map[tmpy + 1]) >= tmpx + 1)
		{
			if (v->m.map[tmpy + 1][tmpx] && v->m.map[tmpy + 1][tmpx] != '1' \
			&& v->m.map[tmpy + 1][tmpx] != c && v->m.map[tmpy + 1][tmpx] != ' ' \
			&& v->m.map[tmpy + 1][tmpx] != '\n')
				v->m.map[tmpy + 1][tmpx] = c;
		}
		tmpx--;
	}
	return (0);
}

int	ft_north_offensive(int x, int y, t_v *v, char c)
{
	int	tmpx;
	int	tmpy;

	tmpy = y;
	tmpx = x;
	while (v->m.map[tmpy][tmpx] && v->m.map[tmpy][tmpx] != '1' \
	&& v->m.map[tmpy][tmpx] != ' ' && v->m.map[tmpy][tmpx] != '\n')
	{
		if (v->m.map[tmpy][tmpx] != '1' && v->m.map[tmpy][tmpx] != c \
		&& v->m.map[tmpy][tmpx] != ' ' && v->m.map[tmpy][tmpx] != '\n')
			v->m.map[tmpy][tmpx] = c;
		if (tmpx - 1 >= 0)
		{
			if (v->m.map[tmpy][tmpx - 1] != '1' && v->m.map[tmpy][tmpx - 1] != c \
			&& v->m.map[tmpy][tmpx - 1] != ' ' && v->m.map[tmpy][tmpx - 1] != '\n')
				v->m.map[tmpy][tmpx - 1] = c;
		}
		if (v->m.map[tmpy][tmpx + 1] && v->m.map[tmpy][tmpx + 1] != '1' \
		&& v->m.map[tmpy][tmpx + 1] != c && v->m.map[tmpy][tmpx + 1] != ' ' \
		&& v->m.map[tmpy][tmpx + 1] != '\n')
			v->m.map[tmpy][tmpx + 1] = c;
		if ((int)ft_strlen(v->m.map[tmpy - 1]) < tmpx + 1)
			break;
		tmpy--;
	}
	return (0);
}

int	ft_east_offensive(int x, int y, t_v *v, char c)
{
	int	tmpx;
	int	tmpy;

	tmpy = y;
	tmpx = x;
	while (v->m.map[tmpy][tmpx] && v->m.map[tmpy][tmpx] != '1' \
	&& v->m.map[tmpy][tmpx] != ' ' && v->m.map[tmpy][tmpx] != '\n')
	{
		if (v->m.map[tmpy][tmpx] != '1' && v->m.map[tmpy][tmpx] != c \
		&& v->m.map[tmpy][tmpx] != ' '&& v->m.map[tmpy][tmpx] != '\n')
			v->m.map[tmpy][tmpx] = c;
		if ((int)ft_strlen(v->m.map[tmpy - 1]) >= tmpx)
		{
			if (v->m.map[tmpy - 1][tmpx] && v->m.map[tmpy - 1][tmpx] != '1' \
			&& v->m.map[tmpy - 1][tmpx] != c && v->m.map[tmpy - 1][tmpx] != ' ' \
			&& v->m.map[tmpy - 1][tmpx] != '\n')
				v->m.map[tmpy - 1][tmpx] = c;
		}
		if ((int)ft_strlen(v->m.map[tmpy + 1]) >= tmpx)
		{
			if (v->m.map[tmpy + 1][tmpx] && v->m.map[tmpy + 1][tmpx] != '1' \
			&& v->m.map[tmpy + 1][tmpx] != c && v->m.map[tmpy + 1][tmpx] != ' ' \
			&& v->m.map[tmpy + 1][tmpx] != '\n')
				v->m.map[tmpy + 1][tmpx] = c;
		}
		tmpx++;
	}
	return (0);
}

int	ft_south_offensive(int x, int y, t_v *v, char c)
{
	int	tmpx;
	int	tmpy;

	tmpy = y;
	tmpx = x;
	while (v->m.map[tmpy][tmpx] && v->m.map[tmpy][tmpx] != '1' \
	&& v->m.map[tmpy][tmpx] != ' ' && v->m.map[tmpy][tmpx] != '\n')
	{
		if (v->m.map[tmpy][tmpx] != '1' && v->m.map[tmpy][tmpx] != c \
		&& v->m.map[tmpy][tmpx] != ' ' && v->m.map[tmpy][tmpx] != '\n')
			v->m.map[tmpy][tmpx] = c;
		if (tmpx - 1 >= 0)
		{
			if (v->m.map[tmpy][tmpx - 1] != '1' \
			&& v->m.map[tmpy][tmpx - 1] != c && v->m.map[tmpy][tmpx - 1] != ' ')
				v->m.map[tmpy][tmpx - 1] = c;
		}
		if (v->m.map[tmpy][tmpx + 1] && v->m.map[tmpy][tmpx + 1] != '1' \
		&& v->m.map[tmpy][tmpx + 1] != c && v->m.map[tmpy][tmpx + 1] != ' ' \
		&& v->m.map[tmpy][tmpx + 1] != '\n')
			v->m.map[tmpy][tmpx + 1] = c;
		if ((int)ft_strlen(v->m.map[tmpy + 1]) < tmpx + 1)
			break;
		tmpy++;
	}
	return (0);
}

int	ft_invasion_propagation(int x, int y, t_v *v, char c)
{
	ft_west_offensive(x, y, v, c);
	ft_north_offensive(x, y, v, c);
	ft_east_offensive(x, y, v, c);
	ft_south_offensive(x, y, v, c);
	return (0);
}

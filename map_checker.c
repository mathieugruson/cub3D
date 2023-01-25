/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chillion <chillion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 18:22:57 by chillion          #+#    #+#             */
/*   Updated: 2023/01/25 17:50:09 by chillion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_invasion_checker_condition(t_v *v, int x, int y, char c)
{
	if (v->m.map[y][x - 1] != '1' && v->m.map[y][x - 1] != c \
	&& v->m.map[y][x - 1] != ' ' && v->m.map[y][x - 1] != 'n')
		return (1);
	if (v->m.map[y][x + 1])
	{
		if (v->m.map[y][x + 1] != '1' && v->m.map[y][x + 1] != c \
		&& v->m.map[y][x + 1] != ' '&& v->m.map[y][x + 1] != '\n')
			return (1);
	}
	if (y - 1 > 0 && (int)ft_strlen(v->m.map[y - 1]) >= x)
	{
		if (v->m.map[y - 1][x] && v->m.map[y - 1][x] != '1' \
		&& v->m.map[y - 1][x] != c && v->m.map[y - 1][x] != ' ' \
		&& v->m.map[y - 1][x] != '\n')
			return (1);
	}
	if ((int)ft_strlen(v->m.map[y + 1]) >= x)
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
	if (v->m.map[y][x - 1] != '1' && v->m.map[y][x - 1] != c \
	&& v->m.map[y][x - 1] != ' ')
		ft_invasion_propagation(x, y, v, c);
	if (v->m.map[y][x + 1])
	{
		if (v->m.map[y][x + 1] != '1' && v->m.map[y][x + 1] != c \
		&& v->m.map[y][x + 1] != ' ')
			ft_invasion_propagation(x, y, v, c);
	}
	if (y - 1 > 0 && (int)ft_strlen(v->m.map[y - 1]) >= x)
	{
		if (v->m.map[y - 1][x] != '1' && v->m.map[y - 1][x] != c \
		&& v->m.map[y - 1][x] != ' ' && v->m.map[y - 1][x])
			ft_invasion_propagation(x, y, v, c);
	}
	if ((int)ft_strlen(v->m.map[y + 1]) >= x)
	{
		if (v->m.map[y + 1][x] != '1' && v->m.map[y + 1][x] != c \
		&& v->m.map[y + 1][x] != ' ' && v->m.map[y + 1][x])
			ft_invasion_propagation(x, y, v, c);
	}
}

int	check_final_wall(t_v *v, char c)
{
	int	x;
	int	y;
	int	i;

	y = 0;
	i = 0;
	while (v->m.map[y])
	{
		x = 0;
		while (v->m.map[y][x])
		{
			if (v->m.map[y][x] == c)
			{
				if (v->m.map[y][x + 1] == '\0' \
				|| v->m.map[y][x + 1] == '\n')
					return (1);
				i = x;
			}
			x++;
		}
		if (y - 1 > 0 && (int)ft_strlen(v->m.map[y - 1]) <= i)
			return (1);
		if (v->m.map[y + 1] && (int)ft_strlen(v->m.map[y + 1]) <= i)
			return (1);
		y++;
	}
	return (0);
}

int	ft_invasion_loop(t_v *v, char c)
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
				ft_invasion_loop_checker(v, x, y, c);
			x++;
		}
		y++;
	}
	ft_print_tab(v->m.map);
	if (ft_invasion_checker(v, c) != 0)
		return (ft_invasion_loop(v, c));
	if (check_final_wall(v, c) == 1)
		return (ft_printf("Error\nPlayer map part is not close by walls\n"), 1);
	return (0);
}

void	ft_argv_check(char *argv, t_v *v)
{
	int	i;

	i = 0;
	(void)v;
	if (!argv)
		return ;
	while (argv[i])
		i++;
	if (i < 4)
	{
		ft_printf("Error\nMap is not .cub file\n");
		exit(EXIT_FAILURE);
	}
	i = i - 4;
	if (argv[i] != '.' || argv[i + 1] != 'c' || argv[i + 2] != 'u' \
	|| argv[i + 3] != 'b')
	{
		ft_printf("Error\nMap is not .cub file\n");
		exit(EXIT_FAILURE);
	}
}
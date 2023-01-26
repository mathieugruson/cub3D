/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 18:22:57 by chillion          #+#    #+#             */
/*   Updated: 2023/01/26 23:11:52 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_final_wall_part_2(t_v *v, int i, int x, int y)
{
	i = x;
	if (x == 0 || y == 0)
		return (8);
	if (y - 1 >= 0 && (int)ft_strlen(v->m.map[y - 1]) <= i)
		return (1);
	if (v->m.map[y + 1] && (int)ft_strlen(v->m.map[y + 1]) <= i)
		return (2);
	if (v->m.map[y][x + 1] != '1' && v->m.map[y][x + 1] != v->pos)
		return (3);
	if (y - 1 >= 0 && (int)ft_strlen(v->m.map[y - 1]) >= x)
	{
		if (v->m.map[y - 1][x] != '1' && v->m.map[y - 1][x] != v->pos)
			return (4);
	}
	if (v->m.map[y + 1] && (int)ft_strlen(v->m.map[y + 1]) >= x)
	{
		if (v->m.map[y + 1][x] != '1' && v->m.map[y + 1][x] != v->pos)
			return (5);
	}
	if (!v->m.map[y + 1])
	{
		if (v->m.map[y][x] != '1' && v->m.map[y][x] != '\n')
			return (6);
	}
	return (0);
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
			if (v->m.map[y][x] == c && check_final_wall_part_2(v, i, x, y) > 0)
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}

int	ft_invasion_loop(t_v *v, char c)
{
	int	x;
	int	y;
	int	i;

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
	if (ft_invasion_checker(v, c) != 0)
		return (ft_invasion_loop(v, c));
	i = check_final_wall(v, c);
	if (i >= 1)
		return (ft_printf("Error\nPlayer map part not closed\n", i), 1);
	return (0);
}

void	ft_argv_check(char *argv)
{
	int	i;

	i = 0;
	if (!argv)
		return ;
	while (argv[i])
		i++;
	if (i <= 4)
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

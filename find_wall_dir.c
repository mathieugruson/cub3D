/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_wall_dir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 12:07:36 by mgruson           #+#    #+#             */
/*   Updated: 2023/01/26 12:07:51 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_wall(char c)
{
	if (c == '0')
		return (0);
	if (c == 'N')
		return (0);
	if (c == 'W')
		return (0);
	if (c == 'S')
		return (0);
	if (c == 'E')
		return (0);
	return (1);
}

void	find_wall_dir_y(t_v *v, double pixely, double pixelx, char *dir)
{
	if (!is_wall(v->m.map[((int)pixely + 2) / XSIZE][(int)pixelx / XSIZE]))
	{
		*dir = 'N';
	}
	else if (!is_wall(v->m.map[((int)pixely - 2) / XSIZE][(int)pixelx / XSIZE]))
	{
		*dir = 'S';
	}
}

void	find_wall_dir_x(t_v *v, double pixely, double pixelx, char *dir)
{
	if (!is_wall(v->m.map[(int)pixely / XSIZE][((int)pixelx + 2) / XSIZE]))
	{
		*dir = 'O';
	}
	else if (!is_wall(v->m.map[(int)pixely / XSIZE][((int)pixelx - 2) / XSIZE]))
	{
		*dir = 'E';
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 20:14:32 by mgruson           #+#    #+#             */
/*   Updated: 2023/01/26 20:17:52 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_wall(char c)
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

void	find_diry(t_v *v, double pixely, double pixelx, char *dir)
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

void	find_dirx(t_v *v, double pixely, double pixelx, char *dir)
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

void	collect_raycat_value_y(t_v *v, t_raycast *rc, int y, int x)
{
	double	resultx;
	double	resulty;
	double	view;
	double	radian;

	resultx = ((double)x - rc->pixelx) * ((double)x - rc->pixelx);
	resulty = ((double)y - rc->pixely) * ((double)y - rc->pixely);
	view = 30 - rc->i;
	radian = (180 - 90 - view) * M_PI / 180;
	find_dirx(v, rc->pixely, rc->pixelx, &rc->dir[rc->index]);
	rc->texture[rc->index] = (int)rc->pixely % v->walle.y;
	rc->tab[rc->index] = sqrt(resultx + resulty);
	rc->tab[rc->index] = rc->tab[rc->index] * sin(radian);
	rc->tab[rc->index] = (v->walle.y / rc->tab[rc->index] * (277 * 3));
}

void	collect_raycat_value_x(t_v *v, t_raycast *rc, int y, int x)
{
	double	resultx;
	double	resulty;
	double	view;
	double	radian;

	resultx = ((double)x - rc->pixelx) * ((double)x - rc->pixelx);
	resulty = ((double)y - rc->pixely) * ((double)y - rc->pixely);
	view = 30 - rc->i;
	radian = (180 - 90 - view) * M_PI / 180;
	find_diry(v, rc->pixely, rc->pixelx, &rc->dir[rc->index]);
	rc->texture[rc->index] = (int)rc->pixelx % v->walle.y;
	rc->tab[rc->index] = sqrt(resultx + resulty);
	rc->tab[rc->index] = rc->tab[rc->index] * sin(radian);
	rc->tab[rc->index] = (v->walle.y / rc->tab[rc->index] * (277 * 3));
}

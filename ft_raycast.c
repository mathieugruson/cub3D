/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 20:22:08 by mgruson           #+#    #+#             */
/*   Updated: 2023/01/24 20:23:17 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	find_diry(t_v *v, double pixely, double pixelx, char *dir)
{
	static int	i = 0;

	i++;
	if (v->m.map[((int)pixely + 2) / XSIZE][(int)pixelx / XSIZE] == '0')
	{
		*dir = 'N';
	}
	if (v->m.map[((int)pixely - 2) / XSIZE][(int)pixelx / XSIZE] == '0')
	{
		*dir = 'S';
	}
	if (*dir != 0 && (*dir < 64 || *dir > 90))
		*dir = *(dir - 1);
}

void	find_dirx(t_v *v, double pixely, double pixelx, char *dir)
{
	static int	i = 0;

	i++;
	if (v->m.map[(int)pixely / XSIZE][((int)pixelx + 2) / XSIZE] == '0')
	{
		*dir = 'O';
	}
	if (v->m.map[(int)pixely / XSIZE][((int)pixelx - 2) / XSIZE] == '0')
	{
		*dir = 'E';
	}
	if (*dir != 0 && (*dir < 64 || *dir > 90))
		*dir = *(dir - 1);
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
	rc->texture[rc->index] = (int)rc->pixely % 64;
	rc->tab[rc->index] = sqrt(resultx + resulty);
	rc->tab[rc->index] = rc->tab[rc->index] * sin(radian);
	rc->tab[rc->index] = (64 / rc->tab[rc->index] * (277 * 3));
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
	rc->texture[rc->index] = (int)rc->pixelx % 64;
	rc->tab[rc->index] = sqrt(resultx + resulty);
	rc->tab[rc->index] = rc->tab[rc->index] * sin(radian);
	rc->tab[rc->index] = (64 / rc->tab[rc->index] * (277 * 3));
}

int	ft_ray_cast(t_v *v, int y, int x, t_raycast *rc)
{
	rc->resultx = find_end_x(rc->left + rc->i);
	rc->resulty = find_end_y(rc->left + rc->i);
	rc->pixelx = x;
	rc->pixely = y;
	rc->pixels = sqrt((rc->resultx * rc->resultx) \
	+ (rc->resulty * rc->resulty));
	rc->resultx /= rc->pixels;
	rc->resulty /= rc->pixels;
	while (1)
	{
		ft_my_mlx_pixel_put(&v->ig, rc->pixely, rc->pixelx, \
		ft_rgb_to_int(0, 50, 150, 250));
		rc->pixelx += rc->resultx;
		if (v->m.map[(int)rc->pixely / XSIZE][(int)rc->pixelx / XSIZE] == '1')
			return (collect_raycat_value_y(v, rc, y, x), 0);
		rc->pixely += rc->resulty;
		if (v->m.map[(int)rc->pixely / XSIZE][(int)rc->pixelx / XSIZE] == '1')
			return (collect_raycat_value_x(v, rc, y, x), 0);
	}
	return (0);
}

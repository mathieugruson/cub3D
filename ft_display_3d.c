/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_3d.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:10:11 by chillion          #+#    #+#             */
/*   Updated: 2023/01/26 12:10:15 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_draw_wall_ratio(t_v *v, t_data d, t_raycast *rc)
{
	int		color;
	double	ratio;
	double	wall_size;
	int		x;
	int		y;

	wall_size = rc->tab[rc->index];
	x = rc->printy + rc->i;
	y = rc->index;
	ratio = ((double)d.y / wall_size);
	ratio *= rc->i;
	color = ft_get_color(&d, rc->texture[rc->index], ratio);
	ft_my_mlx_pixel_put(&v->ig2, x, y, color);
}

void	ft_draw_texture_and_floor(t_v *v, t_raycast *rc)
{
	while (rc->i <= rc->tab[rc->index] && (rc->printy + rc->i) <= 599)
	{
		if (rc->dir[rc->index] == 'N' && (rc->printy + rc->i) > 0)
			ft_draw_wall_ratio(v, v->walln, rc);
		if (rc->dir[rc->index] == 'S' && (rc->printy + rc->i) > 0)
			ft_draw_wall_ratio(v, v->walls, rc);
		if (rc->dir[rc->index] == 'O' && (rc->printy + rc->i) > 0)
			ft_draw_wall_ratio(v, v->wallw, rc);
		if (rc->dir[rc->index] == 'E' && (rc->printy + rc->i) > 0)
			ft_draw_wall_ratio(v, v->walle, rc);
		rc->i++;
	}
	while ((rc->printy + rc->i) > rc->tab[rc->index] \
	&& (rc->printy + rc->i) <= 599)
	{
		ft_my_mlx_pixel_put(&v->ig2, (rc->printy + rc->i), rc->index, \
		ft_rgb_to_int(0, v->valfrgb[0], v->valfrgb[1], v->valfrgb[2]));
		rc->i++;
	}
}

void	init_raycast_value(t_v *v, t_raycast *rc)
{
	rc->right = v->m.degree + 30;
	rc->left = v->m.degree - 30;
	rc->i = 0;
	rc->index = 0;
	if (rc->left < 0)
		rc->left = 360 + rc->left;
	if (rc->right > 360)
		rc->right = rc->right - 360;
}

void	ft_display_3d(t_v *v, int y, int x)
{
	t_raycast	rc;

	init_raycast_value(v, &rc);
	while (rc.index <= 959)
	{
		ft_ray_cast(v, y, x, &rc);
		rc.i = rc.i + 0.0625;
		rc.index++;
		if ((rc.left + rc.i) > 360)
			rc.left = - (360 - rc.left);
	}
	rc.i = 0;
	rc.index = 0;
	while (rc.index <= 959)
	{
		rc.printy = (Y_3D / 2) - (rc.tab[rc.index] / 2);
		while (rc.i < rc.printy && rc.i <= 599)
			ft_my_mlx_pixel_put(&v->ig2, rc.i++, rc.index, \
			ft_rgb_to_int(0, v->valcrgb[0], v->valcrgb[1], v->valcrgb[2]));
		rc.i = 0;
		ft_draw_texture_and_floor(v, &rc);
		rc.i = 0;
		rc.index++;
	}
}

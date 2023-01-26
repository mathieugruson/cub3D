/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 20:22:08 by mgruson           #+#    #+#             */
/*   Updated: 2023/01/26 20:14:42 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		if ((rc->pixely > v->m.ppy - 100) && (rc->pixely < v->m.ppy + 100) && \
		(rc->pixelx > v->m.ppx - 100) && (rc->pixelx < v->m.ppx + 100))
			ft_my_mlx_pixel_put(&v->ig3, 100 - (v->m.ppy - rc->pixely), \
			100 - (v->m.ppx - rc->pixelx), ft_rgb_to_int(0, 50, 150, 250));
		rc->pixelx += rc->resultx;
		if (v->m.map[(int)rc->pixely / XSIZE][(int)rc->pixelx / XSIZE] == '1')
			return (collect_raycat_value_y(v, rc, y, x), 0);
		rc->pixely += rc->resulty;
		if (v->m.map[(int)rc->pixely / XSIZE][(int)rc->pixelx / XSIZE] == '1')
			return (collect_raycat_value_x(v, rc, y, x), 0);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_3d.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:10:11 by chillion          #+#    #+#             */
/*   Updated: 2023/01/24 19:38:37 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_draw_wall(t_v *v, t_data d, int x, int y, double wall_size, double texture, int i)
{
	int			color;
	double		ratio;

	ratio = ((double)64 / wall_size);
	ratio *= i;
	color = ft_get_color(&d, texture, ratio);
	ft_my_mlx_pixel_put(&v->ig2, x, y, color); 
}

void	find_diry(t_v *v, double pixely, double pixelx, char *dir)
{
	static int i = 0;
	i++;
	if (v->m.map[((int)pixely + 2) / XSIZE][(int)pixelx / XSIZE] == '0')
	{
		*dir = 'N'; // OK
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
	static int i = 0;
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
	find_dirx(v, rc->pixely, rc->pixelx, &rc->dir[rc->index]);
	rc->texture[rc->index] = (int)rc->pixely % 64;
	rc->tab[rc->index] = sqrt((((double)x - rc->pixelx) * ((double)x - rc->pixelx)) + (((double)y - rc->pixely) * ((double)y - rc->pixely))); // taille du rayon
	rc->tab[rc->index] = rc->tab[rc->index] * sin((180 - 90 - (30 - rc->i)) * M_PI / 180);  // correction fish eye
	rc->tab[rc->index] = (64 / rc->tab[rc->index] * (277 * 3)); // a l echelle
}

void	collect_raycat_value_x(t_v *v, t_raycast *rc, int y, int x)
{
	find_diry(v, rc->pixely, rc->pixelx, &rc->dir[rc->index]);
	rc->texture[rc->index] = (int)rc->pixelx % 64;
	rc->tab[rc->index] = sqrt((((double)x - rc->pixelx) * ((double)x - rc->pixelx)) + (((double)y - rc->pixely) * ((double)y - rc->pixely))); // taille du rayon
	rc->tab[rc->index] = rc->tab[rc->index] * sin((180 - 90 - (30 - rc->i)) * M_PI / 180);  // correction fish eye
	rc->tab[rc->index] = (64 / rc->tab[rc->index] * (277 * 3)); // a l echelle
}

int	ft_ray_cast(t_v *v, int y, int x, t_raycast *rc)
{
	rc->resultx = find_end_x(rc->left + rc->i); //arrondi
	rc->resulty = find_end_y(rc->left + rc->i); //arrondi
	rc->pixelx = x; 
	rc->pixely = y;
	rc->pixels = sqrt((rc->resultx * rc->resultx) + (rc->resulty * rc->resulty));
	rc->resultx /= rc->pixels;
	rc->resulty /= rc->pixels;
	while (1)
	{
		ft_my_mlx_pixel_put(&v->ig, rc->pixely, rc->pixelx, ft_rgb_to_int(0, 50, 150, 250));
		rc->pixelx += rc->resultx;
		if (v->m.map[(int)rc->pixely / XSIZE][(int)rc->pixelx / XSIZE] == '1')
			return(collect_raycat_value_y(v, rc, y, x), 0);
		rc->pixely += rc->resulty;
		if (v->m.map[(int)rc->pixely / XSIZE][(int)rc->pixelx / XSIZE] == '1')
			return(collect_raycat_value_x(v, rc, y, x), 0);
	}
}

void	ft_display_3d(t_v *v, int y, int x)
{
	t_raycast rc;
	
	rc.right = v->m.degree + 30;
	rc.left = v->m.degree - 30;
	rc.i = 0.0;
	rc.index = 0;
	if (rc.left < 0)
		rc.left = 360 + rc.left;
	if (rc.right > 360)
		rc.right = rc.right - 360;
	while(rc.index <= 959)
	{
		ft_ray_cast(v, y, x, &rc);
		rc.i = rc.i + 0.0625;
		rc.index++;
		if ((rc.left + rc.i) > 360)
			rc.left = - (360 - rc.left);
	}
	rc.i = 0;
	rc.index = 0;
	while(rc.index <= 959)
	{
		rc.printy = (Y_3D / 2) - (rc.tab[rc.index] / 2);
		while(rc.i < rc.printy && rc.i <= 599)
		{
			ft_my_mlx_pixel_put(&v->ig2, rc.i, rc.index, ft_rgb_to_int(0, 255, 255, 0));
			rc.i++;
		}
		rc.i = 0;
		while(rc.i <= rc.tab[rc.index] && (rc.printy + rc.i) <= 599)
		{
			if (rc.dir[rc.index] == 'N' && (rc.printy + rc.i) > 0)
				ft_draw_wall(v, v->walln, (rc.printy + rc.i), rc.index, rc.tab[rc.index], rc.texture[rc.index], rc.i);
			if (rc.dir[rc.index] == 'S' && (rc.printy + rc.i) > 0)
				ft_draw_wall(v, v->walls, (rc.printy + rc.i), rc.index, rc.tab[rc.index], rc.texture[rc.index], rc.i);
			if (rc.dir[rc.index] == 'O' && (rc.printy + rc.i) > 0)
				ft_draw_wall(v, v->wallw, (rc.printy + rc.i), rc.index, rc.tab[rc.index], rc.texture[rc.index], rc.i);
			if (rc.dir[rc.index] == 'E' && (rc.printy + rc.i) > 0)
				ft_draw_wall(v, v->walle, (rc.printy + rc.i), rc.index, rc.tab[rc.index], rc.texture[rc.index], rc.i);
			rc.i++;
		}
		while((rc.printy + rc.i) > rc.tab[rc.index] && (rc.printy + rc.i) <= 599)
		{
			ft_my_mlx_pixel_put(&v->ig2, (rc.printy + rc.i), rc.index, ft_rgb_to_int(0, 0, 255, 255));
			rc.i++;
		}
		rc.i = 0;
		rc.index++;
	}
}
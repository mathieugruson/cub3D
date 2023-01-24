/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:10:11 by chillion          #+#    #+#             */
/*   Updated: 2023/01/24 17:28:39 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_draw_wall(t_v *v, t_data d, int x, int y, double wall_size, double texture, int i)
{
	// double		i;
	// double		j;
	int			color;
	double		ratio;

	// j = 0;
	ratio = ((double)64 / wall_size); // diviser par la taille mur ;
	ratio *= i;
	// printf("ratio %f, wall_size %f, texture %f\n", ratio, wall_size, texture);
	// x = ((920 / 64) * (600 / 64)) / 2 - ((920 / 64) * (600 / 64) / 2); // depart sur l ecran en X
	// y = ((920 / 64) * (600 / 64)) / 2 - ((920 / 64) * (600 / 64) / 2); // depart sur l ecran en Y
	color = ft_get_color(&d, texture, ratio); /* avoir la couleur de l'image a tel enddroit, 
	il faut rajouter a i la distance obtenue avant pr etre sur la bonne colonne */
	ft_my_mlx_pixel_put(&v->ig2, x, y, color); // envoyer
}

// 0.5 ca double la taille
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

void ft_draw_line_dir3d(t_v *v, int y, int x, double degree, double i, double *tab, char *dir, double *texture)
{

	double view = 30 - i; ;
	if (view < 0)
		view *= -1;
	double pi = 3.1415926535897932384626433832;
	double resultx = find_end_x(degree + i); //arrondi
	double resulty = find_end_y(degree + i); //arrondi
	double pixelx = x; 
	double pixely = y;
	int pixels = sqrt((resultx * resultx) + (resulty * resulty));
	resultx /= pixels;
	resulty /= pixels;
	while (1)
	{
		ft_my_mlx_pixel_put(&v->ig, pixely, pixelx, ft_rgb_to_int(0, 50, 150, 250));
		pixelx += resultx;
		if (v->m.map[(int)pixely / XSIZE][(int)pixelx / XSIZE] == '1')
		{
			find_dirx(v, pixely, pixelx, dir);
			*texture = (int)pixely % 64;
			// printf("texturex : %f\n", *texture);
			double distx = ((double)x - pixelx);
			if (distx < 0)
				distx *= -1;
			double disty = ((double)y - pixely);
			if (disty < 0)
				disty *= -1;
			*tab = sqrt((distx * distx) + (disty * disty)); // taille du rayon
			*tab = *tab * sin((180 - 90 - view) * pi / 180);  // correction fish eye
			*tab = (64 / *tab * (277 * 3)); // a l echelle
			return ;
		}
		pixely += resulty;
		if (v->m.map[(int)pixely / XSIZE][(int)pixelx / XSIZE] == '1')
		{
			find_diry(v, pixely, pixelx, dir);
			*texture = (int)pixelx % 64;
			// printf("texturey : %f\n", *texture);
			double distx = ((double)x - pixelx);
			if (distx < 0)
				distx *= -1;
			double disty = ((double)y - pixely);
			if (disty < 0)
				disty *= -1;
			*tab = sqrt((distx * distx) + (disty * disty)); // taille du rayon
			*tab = *tab * sin((180 - 90 - view) * pi / 180);  // correction fish eye
			*tab = (64 / *tab * (277 * 3)); // a l echelle
			return ;
		}
	}
}

void	ft_draw_line_circle3d(t_v *v, int y, int x)
{
	int right = v->m.degree + 30;
	double left = v->m.degree - 30;
	double i = 0.0;
	int index = 0;
	
	double	tab[960];
	char	dir[960];
	double	texture[960];
	if (left < 0)
		left = 360 + left;
	if (right > 360)
		right = right - 360;
	while(index <= 959)
	{
		ft_draw_line_dir3d(v, y, x, left,  i, &tab[index], &dir[index], &texture[index]);
		i = i + 0.0625;
		index++;
		if ((left + i) > 360)
			left = - (360 - left);
	}
	int z = 0;
	index = 0;
	while(index <= 959)
	{
		double printy = (Y_3D / 2) - (tab[index] / 2);
		if (printy < 0)
			printy = 0;
		while(z < printy && z <= 599)
		{
			ft_my_mlx_pixel_put(&v->ig2, z, index, ft_rgb_to_int(0, 255, 255, 0));
			z++;
		}
		z = 0;
		while(z <= tab[index] && z <= 599)
		{
			if (dir[index] == 'N')
			{
				// ft_my_mlx_pixel_put(&v->ig2, (printy + z), index, ft_rgb_to_int(0, 255, 165, 0));
				ft_draw_wall(v, v->walln, (printy + z), index, tab[index], texture[index], z);
			}
			if (dir[index] == 'S')
			{
				// ft_my_mlx_pixel_put(&v->ig2, (printy + z), index, ft_rgb_to_int(0, 255, 69, 0));
				ft_draw_wall(v, v->walln, (printy + z), index, tab[index], texture[index], z);
			}
			if (dir[index] == 'O')
			{
				// ft_my_mlx_pixel_put(&v->ig2, (printy + z), index, ft_rgb_to_int(0, 255, 255, 224));
				ft_draw_wall(v, v->walln, (printy + z), index, tab[index], texture[index], z);
			}
			if (dir[index] == 'E')
			{
				// ft_my_mlx_pixel_put(&v->ig2, (printy + z), index, ft_rgb_to_int(0, 173, 79, 9));
				ft_draw_wall(v, v->walln, (printy + z), index, tab[index], texture[index], z);
			}
			z++;
		}
		while((printy + z) > tab[index] && (printy + z) <= 599)
		{
			ft_my_mlx_pixel_put(&v->ig2, (printy + z), index, ft_rgb_to_int(0, 0, 255, 255));
			z++;
		}
		z = 0;
		index++;
	}
	// ft_draw_wall(v, v->walle, 0, 0);

}
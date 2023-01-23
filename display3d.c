/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:10:11 by chillion          #+#    #+#             */
/*   Updated: 2023/01/23 13:47:37 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	find_dir(t_v *v, double pixely, double pixelx, char *dir)
{
	if (v->m.map[((int)pixely + 10) / XSIZE][(int)pixelx / XSIZE] == '0')
		*dir = 'N'; // OK
	else if (v->m.map[((int)pixely - 10) / XSIZE][(int)pixelx / XSIZE] == '0')
		*dir = 'S'; // OK
	else if (v->m.map[(int)pixely / XSIZE][((int)pixelx + 10) / XSIZE] == '0')
		*dir = 'O';
	else if (v->m.map[((int)pixely + 1) / XSIZE][((int)pixelx - 10) / XSIZE] == '0')
		*dir = 'E';
	else
		*dir = 'Z';
}

void ft_draw_line_dir3d(t_v *v, int y, int x, double degree, double i, double *tab, char *dir)
{
	// y = y + (XSIZE / 2);
	// x = x + (XSIZE / 2);
	double view = 30 - i; ;
	if (view < 0)
		view *= -1;
	// printf("view = %f\n", view);
	// printf("degree : %f, i : %f degree + i : %f\n", degree, i, (degree + i));
	double pi = 3.1415926535897932384626433832;
	double resultx = find_end_x(degree + i); //arrondi
	double resulty = find_end_y(degree + i); //arrondi
	// printf("y %i, x %i\n", y, x);
	// printf("resutly %f, resultx %f\n", resulty, resultx);
	double pixelx = x; //ATTENTION : qd j enleve ca ca marche voir avec cyril */;
	double pixely = y; //ATTENTION : qd j enleve ca ca marche voir avec cyril */;
	// printf("pixely %f, pixelx %f\n", pixely, pixelx);
	int pixels = sqrt((resultx * resultx) + (resulty * resulty));
	resultx /= pixels;
	resulty /= pixels;
	while (1)
	{
		if (v->m.map[(int)pixely / XSIZE][(int)pixelx / XSIZE] == '1')
		{
			find_dir(v, pixely, pixelx, dir);
			printf("dir : %c\n", *dir);
			// printf("y : %i, pixely : %f, x : %i, pixelx %f\n", y, pixely, x, pixelx);
			double distx = ((double)x - pixelx);
			if (distx < 0)
				distx *= -1;
			double disty = ((double)y - pixely);
			if (disty < 0)
				disty *= -1;
			*tab = sqrt((distx * distx) + (disty * disty)); // taille du rayon
			// printf("distance simple : %f\n", *tab);
			*tab = *tab * sin((180 - 90 - view) * pi / 180);  // correction fish eye
			// printf("distance fish eye : %f\n", *tab);
			*tab = (64 / *tab * 277); // a l echelle
			// printf("distance echelle : %f\n", *tab);
			return ;
		}
		// printf(" while y : %i, pixely : %f, x : %i, pixelx %f\n", y, pixely, x, pixelx);
		ft_my_mlx_pixel_put(&v->ig, pixely, pixelx, ft_rgb_to_int(0, 50, 150, 250));
		pixelx += resultx;
		pixely += resulty;
	}
}

void	ft_draw_line_circle3d(t_v *v, int y, int x)
{
	int right = v->m.degree + 30;
	double left = v->m.degree - 30;
	double i = 0.0;
	int index = 0;
	
	double	tab[320];
	char	dir[320];
	if (left < 0)
		left = 360 + left;
	if (right > 360)
		right = right - 360;
	/* METRIC 1/2 */
	// printf("degree : %i\n", v->m.degree);
	/**/
	while(index <= 320)
	{
		/* METRICS  2/2*/
		// printf("index : %i\n", index);
		// printf("left : %f, i %f, left + i : %f\n", left, i, (left + i));
		/**/
		// printf("index %i\n", index);
		ft_draw_line_dir3d(v, y, x, left,  i, &tab[index], &dir[index]);
		i = i + 0.1875;
		index++;
		if ((left + i) > 360)
			left = - (360 - left);
	}
	int z = 0;
	index = 0;
	while(index <= 319)
	{
		/* METRIC 1/1*/
		// printf("index : %i\n", index);
		// printf("column size avant mise a l echelle: %f\n", tab[index]);
		/**/
		/* METRIC 2/2*/
		// printf("column size apres mise a l'echelle : %f\n", tab[index]);
		/**/
		double printy = 100 - (tab[index] / 2);
		if (printy < 0)
			printy = 0;
		while(z < printy && z <= 200)
		{
			ft_my_mlx_pixel_put(&v->ig2, z, index, ft_rgb_to_int(0, 255, 255, 0));
			z++;
		}
		z = 0;
		while(z <= tab[index] && z <= 200)
		{
			if (dir[index] == 'N')
				ft_my_mlx_pixel_put(&v->ig2, (printy + z), index, ft_rgb_to_int(0, 255, 0, 255));
			if (dir[index] == 'S')
				ft_my_mlx_pixel_put(&v->ig2, (printy + z), index, ft_rgb_to_int(0, 255, 50, 255));
			if (dir[index] == 'O')
				ft_my_mlx_pixel_put(&v->ig2, (printy + z), index, ft_rgb_to_int(0, 255, 100, 255));
			if (dir[index] == 'E')
				ft_my_mlx_pixel_put(&v->ig2, (printy + z), index, ft_rgb_to_int(0, 255, 150, 255));
			z++;
		}
		while((printy + z) > tab[index] && (printy + z) <= 200)
		{
			ft_my_mlx_pixel_put(&v->ig2, (printy + z), index, ft_rgb_to_int(0, 0, 255, 255));
			z++;
		}
		z = 0;
		index++;
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:10:11 by chillion          #+#    #+#             */
/*   Updated: 2023/01/22 14:34:42 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void ft_draw_line_dir3d(t_v *v, int y, int x, double degree, double i, double *tab)
{
	(void)y;
	double pi = 3.1415926535897932384626433832;
	double resultx = find_end_x(degree + i); //arrondi
	double resulty = find_end_y(degree + i); //arrondi
	double pixelx = x + (XSIZE / 2);
	double pixely = y + (XSIZE / 2);
	int pixels = sqrt((resultx * resultx) + (resulty * resulty));
	resultx /= pixels;
	resulty /= pixels;
	double view = 30 - i; ;
	if (view < 0)
		view *= -1;
	while (1)
	{
		if (v->m.map[(int)pixely / XSIZE][(int)pixelx / XSIZE] == '1')
		{
			*tab = ((y - pixely) * sin((90) * pi / 180) / sin((180 - 90 - (view)) * pi / 180));	// taille avec fish eye
			// il faut peut etre stocker pixely du centre. comment faire ? lancer un rayon a angle 0 et le garder
			*tab = *tab * cos((view) * pi / 180);  // correction fish eye
			return ;
		}
		ft_my_mlx_pixel_put(&v->ig, pixely, pixelx, ft_rgb_to_int(0, 50, 150, 250));
		pixelx += resultx;
		pixely += resulty;
	}
	// mlx_put_image_to_window(v->mlx, v->win, v->ig.img, 0, 0);

}

void	ft_draw_line_circle3d(t_v *v, int y, int x)
{
	int right = v->m.degree + 30;
	double left = v->m.degree - 30;
	double i = 0.0;
	int index = 0;
	
	double tab[320];
	if (left < 0)
		left = 360 + left;
	if (right > 360)
		right = right - 360;
	/* METRIC 1/ */
	printf("degree : %i\n", v->m.degree);
	/**/
	while(index <= 320)
	{
		/* METRICS  2/*/
		printf("index : %i\n", index);
		printf("left : %f, i %f, left + i : %f\n", left, i, (left + i));
		/**/
		ft_draw_line_dir3d(v, y, x, left,  i, &tab[index]);
		i = i + 0.1875;
		index++;
		if ((left + i) > 360)
			left = - (360 - left);
	}
	int z = 0;
	index = 0;
	while(index <= 320)
	{
		tab[index] = ((double)(64 / tab[index] * 277)); // a l echelle
		while(z <= tab[index])
		{
			ft_my_mlx_pixel_put(&v->ig2, ((tab[index] / 2) + z), (index + 2), ft_rgb_to_int(0, 255, 0, 255));
			z++;
		}
		z = 0;
		index++;
	}
}
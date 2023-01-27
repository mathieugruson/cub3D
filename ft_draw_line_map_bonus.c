/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_line_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 17:46:40 by mgruson           #+#    #+#             */
/*   Updated: 2023/01/26 20:24:42 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_line_mini_map(t_v *v, int i, int j)
{
	if ((i > v->m.ppy - 100) && (i < v->m.ppy + 100) && \
	(j > v->m.ppx - 100) && (j < v->m.ppx + 100))
		ft_my_mlx_pixel_put(&v->ig3, 100 - (v->m.ppy - i), \
		100 - (v->m.ppx - j), ft_rgb_to_int(0, 255, 255, 255));
}

void	ft_draw_line_map(t_v *v)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < (v->m.y * XSIZE))
	{
		while (j < (v->m.x * XSIZE))
		{
			if (j % XSIZE == 0 && j != 0 && j < (v->m.x * XSIZE) \
			&& i < ((v->m.y) * XSIZE))
				draw_line_mini_map(v, i, j);
			if (i % XSIZE == 0 && i != 0 && j < (v->m.x * XSIZE) \
			&& i < ((v->m.y) * XSIZE))
				draw_line_mini_map(v, i, j);
			j++;
		}
		j = 0;
		i++;
	}
}

void	ft_paint_map(t_v *v, int y, int x)
{
	int	i;
	int	j;

	(void)y;
	(void)x;
	i = 0;
	while (i < XSIZE)
	{
		j = 0;
		while (j < XSIZE)
		{
			if (j != 0 && (((y * XSIZE) + i) > v->m.ppy - 100) && \
			(((y * XSIZE) + i) < v->m.ppy + 100) && \
			(((x * XSIZE) + j) > v->m.ppx - 100) && \
			(((x * XSIZE) + j) < v->m.ppx + 100))
				ft_my_mlx_pixel_put(&v->ig3, 100 - (v->m.ppy - ((y * XSIZE) \
				+ i)), 100 - (v->m.ppx - ((x * XSIZE) + j)), \
				ft_rgb_to_int(0, 255, 255, 255));
			j++;
		}
		i++;
	}
}

void	ft_draw_player_dir(t_v *v, int degree)
{
	t_raycast	r;

	r.resultx = find_end_x(degree);
	r.resulty = find_end_y(degree);
	r.pixelx = v->m.ppx;
	r.pixely = v->m.ppy;
	r.pixels = sqrt((r.resultx * r.resultx) + (r.resulty * r.resulty));
	r.resultx /= r.pixels;
	r.resulty /= r.pixels;
	r.i = -1;
	while (1)
	{
		if (v->m.map[((int)r.pixely) / XSIZE][(int)r.pixelx / XSIZE] == '1' || \
		v->m.map[(int)r.pixely / XSIZE][((int)r.pixelx) / XSIZE] == '1')
			break ;
		if ((r.pixely > v->m.ppy - 100) && (r.pixely < v->m.ppy + 100) && \
		(r.pixelx > v->m.ppx - 100) && (r.pixelx < v->m.ppx + 100))
			ft_my_mlx_pixel_put(&v->ig3, 100 - (v->m.ppy - r.pixely), 100 - \
			(v->m.ppx - r.pixelx), ft_rgb_to_int(0, 250, 250, 250));
		mlx_put_image_to_window(v->mlx, v->win, v->ig3.img, 20, 380);
		r.pixelx += r.resultx;
		r.pixely += r.resulty;
		if (r.i++ == (XSIZE / 10))
			break ;
	}
}

void	ft_paint_player_pixel(t_v *v, int y, int x)
{
	int	right;
	int	left;

	(void)y;
	(void)x;
	right = v->m.degree + 90;
	left = v->m.degree - 90;
	if (right > 360)
		right = right - 360;
	if (left < 0)
		left = 360 + left;
	ft_draw_player_dir(v, v->m.degree);
	ft_draw_player_dir(v, right);
	ft_draw_player_dir(v, left);
}

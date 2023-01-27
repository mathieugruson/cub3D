/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moove_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:01:48 by chillion          #+#    #+#             */
/*   Updated: 2023/01/27 21:34:21 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_moove_display(t_v *v)
{
	if (v->ig2.img)
		mlx_destroy_image(v->mlx, v->ig2.img);
	v->ig2.img = mlx_new_image(v->mlx, 960, 600);
	if (!v->ig2.img)
		ft_close_event(v);
	v->ig2.ad = mlx_get_data_addr(v->ig2.img, &v->ig2.bpp, \
	&v->ig2.llen, &v->ig2.en);
	if (v->ig3.img)
		mlx_destroy_image(v->mlx, v->ig3.img);
	v->ig3.img = mlx_new_image(v->mlx, 200, 200);
	if (!v->ig3.img)
		ft_close_event(v);
	v->ig3.ad = mlx_get_data_addr(v->ig3.img, &v->ig3.bpp, \
	&v->ig3.llen, &v->ig3.en);
	ft_draw_line_map(v);
	ft_check_pix_map(v);
	ft_paint_player_pixel(v, v->m.ppy, v->m.ppx);
	ft_display_3d(v, v->m.ppy, v->m.ppx);
}

int	ft_moove_player(t_v *v, int degree)
{
	double	tmp_ppx;
	double	tmp_ppy;
	double	tmp_ppx2;
	double	tmp_ppy2;

	tmp_ppx = ((v->m.ppx + find_wall_x(v->m.degree + degree)) / XSIZE);
	tmp_ppy = ((v->m.ppy + find_wall_y(v->m.degree + degree)) / XSIZE);
	tmp_ppx2 = ((v->m.ppx - 5 + find_wall_x(v->m.degree + degree)) / XSIZE);
	tmp_ppy2 = ((v->m.ppy - 5 + find_wall_y(v->m.degree + degree)) / XSIZE);
	if (v->m.map[(int)tmp_ppy][(int)tmp_ppx] == '1')
		return (0);
	tmp_ppx = ((v->m.ppx + 5 + find_wall_x(v->m.degree + degree)) / XSIZE);
	tmp_ppy = ((v->m.ppy + 5 + find_wall_y(v->m.degree + degree)) / XSIZE);
	if (v->m.map[(int)tmp_ppy][(int)tmp_ppx] == '1' || \
	v->m.map[(int)tmp_ppy2][(int)tmp_ppx2] == '1')
		return (0);
	if (v->m.map[(int)tmp_ppy2][(int)tmp_ppx] == '1' || \
	v->m.map[(int)tmp_ppy][(int)tmp_ppx2] == '1')
		return (0);
	v->m.py = (v->m.ppy / XSIZE);
	ft_new_player_pos(v, v->m.ppy, v->m.ppx, v->m.degree + degree);
	return (ft_moove_display(v), 1);
}

int	ft_moove_ray(t_v *v, int sense)
{
	v->m.degree += sense;
	if (v->m.degree == -5)
		v->m.degree = 355;
	if (v->m.degree == 365)
		v->m.degree = 5;
	ft_moove_display(v);
	return (1);
}

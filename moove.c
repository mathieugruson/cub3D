/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moove.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:01:48 by chillion          #+#    #+#             */
/*   Updated: 2023/01/25 12:23:39 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	moove_player(int dir, t_v *v)
{
	if (dir == 'W')
		dir = ft_moove_player(v, 0);
	if (dir == 'S')
		dir = ft_moove_player(v, 180);
	if (dir == 'D')
		dir = ft_moove_player(v, 90);
	if (dir == 'A')
		dir = ft_moove_player(v, 270);
	if (dir == 'K')
		dir = ft_moove_ray(v, 5);
	if (dir == 'H')
		dir = ft_moove_ray(v, (-5));
	if (dir == 1)
	{
		// mlx_put_image_to_window(v->mlx, v->win, v->ig.img, 0, 0);
		mlx_put_image_to_window(v->mlx, v->win, v->ig2.img, 0, 0);
	}
}

int	ft_keypress_event(int key, t_v *v)
{
	// ft_printf("1v->m.py=%d et v->m.px=%d\n", v->m.py, v->m.px);
	if (key == 119) // || key == 65362)
		moove_player('W', v);
	if (key == 115) //|| key == 65364)
		moove_player('S', v);
	if (key == 100)
		moove_player('D', v);
	if (key == 97)
		moove_player('A', v);
	if (key == 65363)
		moove_player('K', v);
	if (key == 65361)
		moove_player('H', v);
	if (key == 65307)
		ft_close_event(v);
	return (0);
}

double	find_wall_x(double degree)
{
	// degree to gradian : 350° × π/180 = 6,109rad
	/* entre 0 et 180 on renvoie +x et entre 180 et 360 on renvoie -x*/
	double pi = 3.1415926535897932384626433832;
	double res = 0;

	res = 13 * sin((degree) * pi / 180);
	// printf("resx : %f\n", res);
	return (res);
}

double	find_wall_y(double degree)
{
	double pi = 3.1415926535897932384626433832;
	double res = 0;
	res = 13 * cos((degree) * pi / 180);
	// printf("resy : %f\n", res);
	return (res * -1);
}

void	ft_moove_display(t_v *v)
{
	if (v->ig.img)
		mlx_destroy_image(v->mlx, v->ig.img);
	v->ig.img = mlx_new_image(v->mlx, ((v->m.x) * XSIZE), (v->m.y * XSIZE));
	if (!v->ig.img)
		ft_stop_all(v, 1);
	v->ig.ad = mlx_get_data_addr(v->ig.img, &v->ig.bpp, &v->ig.llen, &v->ig.en);
	if (v->ig2.img)
		mlx_destroy_image(v->mlx, v->ig2.img);
	v->ig2.img = mlx_new_image(v->mlx, 960, 600);
	if (!v->ig2.img)
		ft_stop_all(v, 1);
	v->ig2.ad = mlx_get_data_addr(v->ig2.img, &v->ig2.bpp, &v->ig2.llen, &v->ig2.en);
	ft_draw_line_map(v);
	ft_check_pix_map(v);
	ft_draw_pix_line_circle(v, v->m.ppy, v->m.ppx);
	ft_paint_player_pixel(v, v->m.ppy, v->m.ppx);
	ft_display_3d(v, v->m.ppy, v->m.ppx);
}

int	ft_moove_player(t_v *v, int degree)
{
	double tmp_ppx = v->m.ppx + find_wall_x(v->m.degree + degree);
	tmp_ppx = (tmp_ppx / XSIZE);
	double tmp_ppy = v->m.ppy + find_wall_y(v->m.degree + degree);
	tmp_ppy = (tmp_ppy / XSIZE);
	if (v->m.map[(int)tmp_ppy][(int)tmp_ppx] == '1')
		return (0);
	ft_new_player_pos(v, v->m.ppy, v->m.ppx, v->m.degree + degree);
	ft_moove_display(v);
	v->m.py = (v->m.ppy / XSIZE);
	return (1);
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

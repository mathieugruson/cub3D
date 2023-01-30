/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 10:46:25 by mgruson           #+#    #+#             */
/*   Updated: 2023/01/30 11:28:39 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_close_event(t_v *v)
{
	ft_clean_tstr(v->m.map, 0);
	ft_clean_tstr(v->args, 0);
	if (v->walle.img)
		mlx_destroy_image(v->mlx, v->walle.img);
	if (v->walln.img)
		mlx_destroy_image(v->mlx, v->walln.img);
	if (v->walls.img)
		mlx_destroy_image(v->mlx, v->walls.img);
	if (v->wallw.img)
		mlx_destroy_image(v->mlx, v->wallw.img);
	if (v->ig2.img)
		mlx_destroy_image(v->mlx, v->ig2.img);
	if (v->ig3.img)
		mlx_destroy_image(v->mlx, v->ig3.img);
	if (v->win)
		mlx_destroy_window(v->mlx, v->win);
	if (v->mlx)
	{
		mlx_destroy_display(v->mlx);
		free(v->mlx);
	}
	exit(0);
}

double	find_end_x(double degree)
{
	double	res;

	res = 0;
	res = 10 * sin((degree) * M_PI / 180);
	return (res);
}

double	find_end_y(double degree)
{
	double	res;

	res = 0;
	res = 10 * cos((degree) * M_PI / 180);
	return (res * -1);
}

void	ft_new_player_pos(t_v *v, double y, double x, int degree)
{
	t_raycast	r;

	r.resultx = find_end_x(degree);
	r.resulty = find_end_y(degree);
	r.pixelx = x;
	r.pixely = y;
	r.pixels = sqrt((r.resultx * r.resultx) + (r.resulty * r.resulty));
	r.i = 0;
	r.resultx /= r.pixels;
	r.resulty /= r.pixels;
	while (r.i < 10)
	{
		if (v->m.map[((int)r.pixely) / XSIZE][(int)r.pixelx / XSIZE] == '1' || \
		v->m.map[(int)r.pixely / XSIZE][((int)r.pixelx) / XSIZE] == '1')
			break ;
		r.pixelx += r.resultx;
		r.pixely += r.resulty;
		r.i++;
	}
	v->m.ppx = r.pixelx;
	v->m.ppy = r.pixely;
}

int	main(int argc, char **argv)
{
	t_v	var;

	(void)argc;
	(void)argv;
	if (argc == 2)
	{
		ft_argv_check(argv[1]);
		ft_init_data(&var);
		ft_parsing_map(argv[1], &var);
		init_degree(&var);
		ft_init_mlx(&var);
		return (0);
	}
	return (ft_printf("Error\nCub3D need one argument (ex : MAP.cub).\n"), 0);
}

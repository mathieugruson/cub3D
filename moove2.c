/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moove2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 19:36:57 by mgruson           #+#    #+#             */
/*   Updated: 2023/01/26 19:51:20 by mgruson          ###   ########.fr       */
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
		mlx_put_image_to_window(v->mlx, v->win, v->ig2.img, 0, 0);
		mlx_put_image_to_window(v->mlx, v->win, v->ig3.img, 20, 380);
	}
}

int	ft_keypress_event(int key, t_v *v)
{
	if (key == 119)
		moove_player('W', v);
	if (key == 115)
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
	double	res;

	res = 0;
	res = 13 * sin((degree) * M_PI / 180);
	return (res);
}

double	find_wall_y(double degree)
{
	double	res;

	res = 0;
	res = 13 * cos((degree) * M_PI / 180);
	return (res * -1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:55:56 by mgruson           #+#    #+#             */
/*   Updated: 2023/01/24 15:28:59 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init_new_sprites(t_v *v)
{
	v->walle.img = mlx_xpm_file_to_image(v->mlx, "tx/walle.xpm", &v->walle.y, &v->walle.x);
	if (!v->walle.img)
		ft_close_event(v);
	v->walle.ad = mlx_get_data_addr(v->walle.img, &v->walle.bpp, &v->walle.llen, &v->walle.en);
	v->walln.img = mlx_xpm_file_to_image(v->mlx, "tx/walln.xpm", &v->walln.y, &v->walln.x);
	if (!v->walln.img)
		ft_close_event(v);
	v->walln.ad = mlx_get_data_addr(v->walln.img, &v->walln.bpp, &v->walln.llen, &v->walln.en);
	v->walls.img = mlx_xpm_file_to_image(v->mlx, "tx/walls.xpm", &v->walls.y, &v->walls.x);
	if (!v->walls.img)
		ft_close_event(v);
	v->walls.ad = mlx_get_data_addr(v->walls.img, &v->walls.bpp, &v->walls.llen, &v->walls.en);
	v->wallw.img = mlx_xpm_file_to_image(v->mlx, "tx/wallw.xpm", &v->wallw.y, &v->wallw.x);
	if (!v->wallw.img)
		ft_close_event(v);
	v->wallw.ad = mlx_get_data_addr(v->wallw.img, &v->wallw.bpp, &v->wallw.llen, &v->wallw.en);
}
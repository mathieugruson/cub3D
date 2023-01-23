/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:55:56 by mgruson           #+#    #+#             */
/*   Updated: 2023/01/23 17:01:50 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	ft_draw_wall(t_v *v, int x, int y)
// {
// 	double		i;
// 	double		j;
// 	int			color;
// 	double		ratio;

// 	j = 0;
// 	ratio = ((double)v->sb.w / (double)(((v->m.h) * v->m.w)));
// 	x = x - (((v->m.h) * v->m.w) / 2);
// 	y = y - (((v->m.h) * v->m.w) / 2);
// 	while (j < (double)((v->m.h) * v->m.w))
// 	{
// 		i = 0;
// 		while (i < (double)((v->m.h) * v->m.w))
// 		{
// 			color = ft_get_color(&v->sb, i * ratio, j * ratio);
// 			if (color != 0x000000FF)
// 				ft_my_mlx_pixel_put(&v->ig, (x + i), (y + j), color);
// 			i++;
// 		}
// 		j++;
// 	}
// }
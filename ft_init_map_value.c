/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_map_value.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 17:21:52 by mgruson           #+#    #+#             */
/*   Updated: 2023/01/26 20:04:29 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_each_value_of_map(t_v *v, int i, int j)
{
	v->m.py = i;
	v->m.px = j;
	v->m.ppy = (i * XSIZE) + (XSIZE / 2);
	v->m.ppx = (j * XSIZE) + (XSIZE / 2);
	v->m.resultx = find_end_x(0);
	v->m.resulty = find_end_y(0);
	v->m.pixelx = v->m.ppx;
	v->m.pixely = v->m.ppy;
	v->m.pixels = sqrt((v->m.resultx * v->m.resultx) + \
	(v->m.resulty * v->m.resulty));
	v->m.resultx /= v->m.pixels;
	v->m.resulty /= v->m.pixels;
}

void	ft_init_map_value(t_v *v)
{
	int	i;
	int	j;

	i = 0;
	if (!v->m.map)
		return ;
	while (v->m.map[i])
	{
		j = 0;
		while (v->m.map[i][j])
		{
			if (v->m.map[i][j] == v->pos)
			{
				init_each_value_of_map(v, i, j);
				break ;
			}
			j++;
		}
		i++;
	}
}

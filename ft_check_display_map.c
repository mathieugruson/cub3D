/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_display_map.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 17:52:05 by mgruson           #+#    #+#             */
/*   Updated: 2023/01/26 20:20:54 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_check_pix_map(t_v *v)
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
			if (v->m.map[i][j] == '1')
				ft_paint_map(v, i, j);
			j++;
		}
		i++;
	}
}

void	ft_check_map(t_v *v)
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
			if (v->m.map[i][j] == '1')
				ft_paint_map(v, i, j);
			if (v->m.map[i][j] == v->pos)
			{
				ft_paint_player_pixel(v, v->m.ppy, v->m.ppx);
			}
			j++;
		}
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_attack2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 19:29:10 by mgruson           #+#    #+#             */
/*   Updated: 2023/01/26 19:31:08 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	propagate_player(t_v *v, int tx, int ty, char c)
{
	if (v->m.map[ty][tx] != '1' && v->m.map[ty][tx] != c \
	&& v->m.map[ty][tx] != ' ' && v->m.map[ty][tx] != '\n')
		v->m.map[ty][tx] = c;
}

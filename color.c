/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 17:38:46 by mgruson           #+#    #+#             */
/*   Updated: 2023/01/26 20:19:36 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_my_mlx_pixel_put(t_data *data, int i, int j, int color)
{
	char	*dst;

	dst = data->ad + (i * data->llen + j * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

unsigned int	ft_get_color(t_data *data, int x, int y)
{
	char	*dst;

	dst = data->ad + (y * data->llen + x * 4);
	return (*(unsigned int *)dst);
}

int	ft_rgb_to_int(int t, int r, int g, int b)
{
	int	color;

	color = 0;
	color |= b;
	color |= g << 8;
	color |= r << 16;
	color |= t << 24;
	return (color);
}

int	get_valrgb(t_v *v, char **tmp, char c)
{
	int	i;

	i = 0;
	while (i < 3 && c == 'C')
	{
		if (ft_onlydigit_atoi(tmp[i]) == 999999999999)
			return (1);
		v->valcrgb[i] = ft_onlydigit_atoi(tmp[i]);
		i++;
	}
	i = 0;
	while (i < 3 && c == 'F')
	{
		if (ft_onlydigit_atoi(tmp[i]) == 999999999999)
			return (1);
		v->valfrgb[i] = ft_onlydigit_atoi(tmp[i]);
		i++;
	}
	return (0);
}

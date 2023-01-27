/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_sprites.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chillion <chillion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 17:17:03 by mgruson           #+#    #+#             */
/*   Updated: 2023/01/27 11:46:30 by chillion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init_sprites_north_south(t_v *v)
{
	char	**tmp;

	tmp = NULL;
	tmp = ft_split(v->valno, ' ');
	tmp[1][ft_strlen(tmp[1]) - 1] = 0;
	v->walln.img = mlx_xpm_file_to_image(v->mlx, tmp[1], \
	&v->walln.x, &v->walln.y);
	ft_clean_tstr(tmp, 0);
	if (!v->walln.img)
		return (ft_printf("Error\nXpm to image failed\n"), \
		ft_close_event(v), (void) 0);
	v->walln.ad = mlx_get_data_addr(v->walln.img, &v->walln.bpp, \
	&v->walln.llen, &v->walln.en);
	tmp = ft_split(v->valso, ' ');
	tmp[1][ft_strlen(tmp[1]) - 1] = 0;
	v->walls.img = mlx_xpm_file_to_image(v->mlx, tmp[1], &v->walls.x, \
	&v->walls.y);
	ft_clean_tstr(tmp, 0);
	if (!v->walls.img)
		return (ft_printf("Error\nXpm to image failed\n"), ft_close_event(v), \
		(void) 0);
	v->walls.ad = mlx_get_data_addr(v->walls.img, &v->walls.bpp, \
	&v->walls.llen, &v->walls.en);
}

void	ft_init_sprites_est_west(t_v *v)
{
	char	**tmp;

	tmp = NULL;
	tmp = ft_split(v->valea, ' ');
	tmp[1][ft_strlen(tmp[1]) - 1] = 0;
	v->walle.img = mlx_xpm_file_to_image(v->mlx, tmp[1], \
	&v->walle.x, &v->walle.y);
	ft_clean_tstr(tmp, 0);
	if (!v->walle.img)
		return (ft_printf("Error\nXpm to image failed\n"), \
		ft_close_event(v), (void) 0);
	v->walle.ad = mlx_get_data_addr(v->walle.img, &v->walle.bpp, \
	&v->walle.llen, &v->walle.en);
	tmp = ft_split(v->valwe, ' ');
	tmp[1][ft_strlen(tmp[1]) - 1] = 0;
	v->wallw.img = mlx_xpm_file_to_image(v->mlx, tmp[1], &v->wallw.x, \
	&v->wallw.y);
	ft_clean_tstr(tmp, 0);
	if (!v->wallw.img)
		return (ft_printf("Error\nXpm to image failed\n"), ft_close_event(v), \
		(void) 0);
	v->wallw.ad = mlx_get_data_addr(v->wallw.img, &v->wallw.bpp, \
	&v->wallw.llen, &v->wallw.en);
}

void	ft_init_sprites(t_v *v)
{
	v->walle.img = 0;
	v->walln.img = 0;
	v->walls.img = 0;
	v->wallw.img = 0;
	ft_init_sprites_north_south(v);
	ft_init_sprites_est_west(v);
	if (v->wallw.x != v->walle.x || v->wallw.x != v->walln.x \
	|| v->wallw.x != v->walls.x)
		return (ft_printf("Error\nSprites size of different sizes\n"), \
		ft_close_event(v), (void) 1);
	if (v->wallw.y != v->walle.x || v->wallw.y != v->walln.x \
	|| v->wallw.y != v->walls.x)
		return (ft_printf("Error\nSprites size of different sizes\n"), \
		ft_close_event(v), (void) 1);
}

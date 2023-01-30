/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 17:43:52 by mgruson           #+#    #+#             */
/*   Updated: 2023/01/30 11:33:57 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**ft_init_tmap(char *argv, int j)
{
	int		fd;
	int		i;
	char	**tmp;

	(void)j;
	fd = open(argv, O_RDONLY);
	if (fd == -1)
		ft_fd_error();
	i = 0;
	tmp = (char **)malloc(sizeof(char *) * (j + 1));
	if (!tmp)
		return (0);
	tmp[j] = 0;
	tmp[i] = get_next_line(fd);
	while (tmp[i])
	{
		i++;
		tmp[i] = get_next_line(fd);
	}
	fd = close(fd);
	return (tmp);
}

void	init_window_and_image(t_v *var)
{
	var->win = mlx_new_window(var->mlx, 960, 600, "cub3D");
	if (!var->win)
		return (mlx_destroy_display(var->mlx), free(var->mlx), exit(1));
	var->ig2.img = mlx_new_image(var->mlx, 960, 600);
	if (!var->ig2.img)
		ft_close_event(var);
	var->ig2.ad = mlx_get_data_addr(var->ig2.img, &var->ig2.bpp, \
	&var->ig2.llen, &var->ig2.en);
	var->ig3.img = mlx_new_image(var->mlx, 200, 200);
	if (!var->ig3.img)
		ft_close_event(var);
	var->ig3.ad = mlx_get_data_addr(var->ig3.img, &var->ig3.bpp, \
	&var->ig3.llen, &var->ig3.en);
}

void	ft_init_mlx(t_v *var)
{
	var->mlx = mlx_init();
	if (!var->mlx)
		return (ft_printf("Error\nMlx failed\n"), ft_close_event(var), exit(1));
	ft_init_sprites(var);
	init_window_and_image(var);
	mlx_hook(var->win, 2, 1L << 0, ft_keypress_event, var);
	mlx_hook(var->win, 17, 1L << 17, ft_close_event, var);
	ft_init_map_value(var);
	ft_draw_line_map(var);
	ft_check_map(var);
	ft_display_3d(var, var->m.ppy, var->m.ppx);
	mlx_put_image_to_window(var->mlx, var->win, var->ig2.img, 0, 0);
	mlx_loop(var->mlx);
}

void	init_degree(t_v *var)
{
	if (var->pos == 'N')
		var->m.degree = 0;
	if (var->pos == 'S')
		var->m.degree = 180;
	if (var->pos == 'E')
		var->m.degree = 90;
	if (var->pos == 'W')
		var->m.degree = 270;
}

void	ft_init_data(t_v *var)
{
	var->m.resultx = 0;
	var->m.resulty = 0;
	var->walle.img = 0;
	var->walln.img = 0;
	var->walls.img = 0;
	var->wallw.img = 0;
	var->ig2.img = 0;
	var->ig3.img = 0;
	var->win = 0;
	var->mlx = 0;
}

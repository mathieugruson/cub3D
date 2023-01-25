/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 10:46:25 by mgruson           #+#    #+#             */
/*   Updated: 2023/01/25 15:28:59 by mgruson          ###   ########.fr       */
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

void	ft_clean_map(t_v *v, int i)
{
	i = 0;
	while (v->m.map[i])
	{
		ft_free(&v->m.map[i]);
		i++;
	}
	free(v->m.map);
}

int	ft_close_event(t_v *v)
{
	ft_clean_map(v, 0);
	if (v->ig.img)
		mlx_destroy_image(v->mlx, v->ig.img);
	if (v->win)
		mlx_destroy_window(v->mlx, v->win);
	if (v->mlx)
	{
		mlx_destroy_display(v->mlx);
		free(v->mlx);
	}
	exit(0);
}

void	ft_init_data(t_v *var)
{
	var->mlx = 0;
	var->win = 0;
	var->ig.img = 0;

	var->ig.bpp = 0;
	var->ig.llen = 0;
	var->ig.en = 0;
	var->ig.ad = 0;
	var->m.degree = 0;
	var->m.degree_status = 0;
	var->m.resultx = 0;
	var->m.resulty = 0;
	var->m.dir = 2;
}

void	ft_stop_all(t_v *v, int exint)
{
	ft_clean_map(v, 0);
	if (v->ig.img)
		mlx_destroy_image(v->mlx, v->ig.img);
	if (!v->win)
		mlx_destroy_window(v->mlx, v->win);
	if (!v->mlx)
	{
		mlx_destroy_display(v->mlx);
		free(v->mlx);
	}
	exit(exint);
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

void	ft_draw_line_map(t_v *v)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < (v->m.y * XSIZE))
	{
		while (j < (v->m.x * XSIZE))
		{
			if (j % XSIZE == 0  && j != 0 && j < (v->m.x * XSIZE) && i < ((v->m.y) * XSIZE))
			{
				if ((i > v->m.ppy - 100) && (i < v->m.ppy + 100) && (j > v->m.ppx - 100) && (j < v->m.ppx + 100))
				{	
					ft_my_mlx_pixel_put(&v->ig3, 100 - (v->m.ppy - i), 100 - (v->m.ppx - j), ft_rgb_to_int(0, 255, 255, 255));
				}
			}
			if (i % XSIZE == 0 && i != 0 && j < (v->m.x * XSIZE) && i < ((v->m.y) * XSIZE))
			{
				if ((i > v->m.ppy - 100) && (i < v->m.ppy + 100) && (j > v->m.ppx - 100) && (j < v->m.ppx + 100))
				{	
					ft_my_mlx_pixel_put(&v->ig3, 100 - (v->m.ppy - i), 100 - (v->m.ppx - j), ft_rgb_to_int(0, 255, 255, 255));
				}
			}
			j++;
		}
		j = 0;
		i++;
	}
}

double find_end_x(double degree)
{
	// degree to gradian : 350° × π/180 = 6,109rad
	/* entre 0 et 180 on renvoie +x et entre 180 et 360 on renvoie -x*/
	double pi = 3.1415926535897932384626433832;
	double res = 0;

	res = 10 * sin((degree) * pi / 180);
	// printf("resx : %f\n", res);
	return (res);
}

double find_end_y(double degree)
{
	double pi = 3.1415926535897932384626433832;
	double res = 0;
	res = 10 * cos((degree) * pi / 180);
	// printf("resy : %f\n", res);
	return (res * -1);
}

void	ft_new_player_pos(t_v *v, double y, double x, int degree)
{
	double resultx = find_end_x(degree);
	double resulty = find_end_y(degree);
	double pixelx = x;
	double pixely = y;
	int pixels = sqrt((resultx * resultx) + (resulty * resulty));
	int i = 0;
	resultx /= pixels;
	resulty /= pixels;
	while (i < 10)
	{
		if (v->m.map[((int)pixely) / XSIZE][(int)pixelx / XSIZE] == '1' || v->m.map[(int)pixely / XSIZE][((int)pixelx) / XSIZE] == '1')
			break ;
		// ft_my_mlx_pixel_put(&v->ig, pixely, pixelx, ft_rgb_to_int(0, 50, 150, 250));
		pixelx += resultx;
		pixely += resulty;
		i++;
	}
	v->m.ppx = pixelx;
	v->m.ppy = pixely;
}

void	ft_paint_map(t_v *v, int y, int x)
{
	int	i;
	int	j;

	(void)y;
	(void)x;
	i = 0;
	while (i < XSIZE)
	{
		j = 0;
		while (j < XSIZE)
		{
			if (j != 0)
			{
				if ((((y * XSIZE) + i) > v->m.ppy - 100) && (((y * XSIZE) + i) < v->m.ppy + 100) && (((x * XSIZE) + j) > v->m.ppx - 100) && (((x * XSIZE) + j) < v->m.ppx + 100))
				{	
					ft_my_mlx_pixel_put(&v->ig3, 100 - (v->m.ppy - ((y * XSIZE) + i)), 100 - (v->m.ppx - ((x * XSIZE) + j)), ft_rgb_to_int(0, 255, 255, 255));
				}
			}
			j++;
		}
		i++;
	}
}

void	ft_draw_player_dir(t_v *v, int degree)
{
	double resultx = find_end_x(degree);
	double resulty = find_end_y(degree);
	double pixelx = v->m.ppx;
	double pixely = v->m.ppy;
	int pixels = sqrt((resultx * resultx) + (resulty * resulty));
	resultx /= pixels;
	resulty /= pixels;
	int i = 0;
	while (1)
	{
		if (v->m.map[((int)pixely) / XSIZE][(int)pixelx / XSIZE] == '1' || v->m.map[(int)pixely / XSIZE][((int)pixelx) / XSIZE] == '1')
			break ;
		if ((pixely > v->m.ppy - 100) && (pixely < v->m.ppy + 100) && (pixelx > v->m.ppx - 100) && (pixelx < v->m.ppx + 100))
		{	
			ft_my_mlx_pixel_put(&v->ig3, 100 - (v->m.ppy - pixely), 100 - (v->m.ppx - pixelx), ft_rgb_to_int(0, 250, 250, 250));
		}
		mlx_put_image_to_window(v->mlx, v->win, v->ig3.img, 20, 380);
		pixelx += resultx;
		pixely += resulty;
		if (i == (XSIZE / 10))
			break;
		i++;
	}
}

void	ft_paint_player_pixel(t_v *v, int y, int x)
{
	(void)y;
	(void)x;
	int right = v->m.degree + 90;
	int left = v->m.degree - 90;

	if (right > 360)
		right = right - 360;
	if (left < 0)
		left = 360 + left;
	ft_draw_player_dir(v, v->m.degree);
	ft_draw_player_dir(v, right);
	ft_draw_player_dir(v, left);
}

void	ft_init_map_value(t_v *v)
{
	int i;
	int j;

	i = 0;
	if (!v->m.map)
		return ;
	while (v->m.map[i])
	{
		j = 0;
		while (v->m.map[i][j])
		{
			if (v->m.map[i][j] == 'P')
			{
				v->m.py = i;
				v->m.px = j;
				v->m.ppy = (i * XSIZE) + (XSIZE / 2);
				v->m.ppx = (j * XSIZE) + (XSIZE / 2);
				v->m.resultx = find_end_x(0);
				v->m.resulty = find_end_y(0);
				v->m.pixelx = v->m.ppx;
				v->m.pixely = v->m.ppy;
				v->m.pixels = sqrt((v->m.resultx * v->m.resultx) + (v->m.resulty * v->m.resulty));
				v->m.resultx /= v->m.pixels;
				v->m.resulty  /= v->m.pixels;
			}
			j++;
		}
		i++;
	}
}

void	ft_check_pix_map(t_v *v)
{
	int i;
	int j;

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
	int i;
	int j;

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
			if (v->m.map[i][j] == 'P') // ATTENTION A MODIFIER 
			{
				ft_paint_player_pixel(v, v->m.ppy, v->m.ppx);
			}
			j++;
		}
		i++;
	}
}

void	ft_init_map(t_v *var)
{
	int i;
	int fd;
	char *str;

	i = 0;
	fd = open("test.map", O_RDONLY);
	if (fd < 0)
		return (ft_printf("%s\n", strerror(errno)), exit(1));
	while (1)
	{
		str = get_next_line(fd);
		if (!str)
			break;
		else
			free(str);
		i++;
	}
	if (i < 1)
		return (write(2, "Error : Map Size\n", 18), exit(1));
	var->m.map = (char **)malloc(sizeof(char *) * (i + 1));
	if (!var->m.map)
		return (exit(1));
	var->m.map[i] = 0;
	i = 0;
	close(fd);
	fd = open("test.map", O_RDONLY);
	while (1)
	{
		var->m.map[i] = get_next_line(fd);
		if (!var->m.map[i])
			break;
		i++;
	}
	var->m.y = i; // H
	var->m.x = ft_strlen(var->m.map[0]) - 1; // W
}

void	ft_init_sprites(t_v *v)
{
	v->walle.img = mlx_xpm_file_to_image(v->mlx, "tx/walle.xpm", &v->walle.x, &v->walle.y);
	if (!v->walle.img)
		ft_close_event(v);
	v->walle.ad = mlx_get_data_addr(v->walle.img, &v->walle.bpp, &v->walle.llen, &v->walle.en);
	v->walln.img = mlx_xpm_file_to_image(v->mlx, "tx/walln.xpm", &v->walln.x, &v->walln.y);
	if (!v->walln.img)
		ft_close_event(v);
	v->walln.ad = mlx_get_data_addr(v->walln.img, &v->walln.bpp, &v->walln.llen, &v->walln.en);
	v->walls.img = mlx_xpm_file_to_image(v->mlx, "tx/walls.xpm", &v->walls.x, &v->walls.y);
	if (!v->walls.img)
		ft_close_event(v);
	v->walls.ad = mlx_get_data_addr(v->walls.img, &v->walls.bpp, &v->walls.llen, &v->walls.en);
	v->wallw.img = mlx_xpm_file_to_image(v->mlx, "tx/wallw.xpm", &v->wallw.x, &v->wallw.y);
	if (!v->wallw.img)
		ft_close_event(v);
	v->wallw.ad = mlx_get_data_addr(v->wallw.img, &v->wallw.bpp, &v->wallw.llen, &v->wallw.en);
}

void	ft_init_mlx(t_v *var)
{
	var->mlx = mlx_init();
	if (!var->mlx)
		return (exit(1));
	ft_init_sprites(var);
	var->win = mlx_new_window(var->mlx, 960, 600, "cub3D");
	if (!var->win)
		return (mlx_destroy_display(var->mlx), free(var->mlx), exit(1));
	var->ig2.img = mlx_new_image(var->mlx, 960, 600);
	if (!var->ig2.img)
		ft_stop_all(var, 1);
	var->ig2.ad = mlx_get_data_addr(var->ig2.img, &var->ig2.bpp, &var->ig2.llen, &var->ig2.en);

	var->ig3.img = mlx_new_image(var->mlx, 200, 200);
	if (!var->ig3.img)
		ft_stop_all(var, 1);
	var->ig3.ad = mlx_get_data_addr(var->ig3.img, &var->ig3.bpp, &var->ig3.llen, &var->ig3.en);
	
	mlx_hook(var->win, 2, 1L << 0, ft_keypress_event, var);
	mlx_hook(var->win, 17, 1L << 17, ft_close_event, var);
	ft_init_map_value(var);
	ft_draw_line_map(var);
	ft_check_map(var);
	ft_display_3d(var, var->m.ppy, var->m.ppx);
	mlx_put_image_to_window(var->mlx, var->win, var->ig2.img, 0, 0);
	mlx_put_image_to_window(var->mlx, var->win, var->ig3.img, 20, 380);
	mlx_loop(var->mlx);
}

int	main(void)
{
	t_v var;

	ft_init_map(&var);
	ft_init_data(&var);
	ft_init_mlx(&var);
	exit(0);
}
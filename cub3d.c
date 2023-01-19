/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 10:46:25 by mgruson           #+#    #+#             */
/*   Updated: 2023/01/19 16:29:34 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef struct s_data {
	void	*img;
	char	*ad;
	int		pos;
	int		addr_use;
	int		bpp;
	int		llen;
	int		en;
	int		x;
	int		y;
	int		color1;
	int		color2;
	int		color3;
}	t_data;

typedef struct s_map
{
	char	**map;
	int		x;
	int		y;
	int		px;
	int		py;
}	t_map;

typedef struct s_var
{
	void	*mlx;
	void	*win;
	t_data	ig;
	t_map	m;
}	t_v;

#define XSIZE 64

void	ft_my_mlx_pixel_put(t_data *data, int i, int j, int color)
{
	char	*dst;

	dst = data->ad + (i * data->llen + j * (data->bpp / 8));
	*(unsigned int *)dst = color;
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

int	ft_keypress_event(int key, t_v *v)
{
	// if (key == 65362 || key == 119)
	// if (key == 65364 || key == 115)
	// if (key == 65363 || key == 100)
	// if (key == 65361 || key == 97)
	if (key == 65307)
		ft_close_event(v);
	return (0);
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
	while (i < ((v->m.y) * XSIZE))
	{
		while (j < (v->m.x * XSIZE))
		{
			if (j % XSIZE == 0  && j != 0)
			{
				ft_my_mlx_pixel_put(&v->ig, i, j, \
				ft_rgb_to_int(0, 255, 255, 255));
			}
			if (i % XSIZE == 0 && i != 0)
			{
				ft_my_mlx_pixel_put(&v->ig, i, j,
				ft_rgb_to_int(0, 255, 255, 255));
			}
			j++;
		}
		j = 0;
		i++;
	}
}

double find_end_x(int degree)
{
	// degree to gradian : 350° × π/180 = 6,109rad
	/* entre 0 et 180 on renvoie +x et entre 180 et 360 on renvoie -x*/
	double pi = 3.1415926535897932384626433832;
	double res = 0;

	res = 10 *sin((degree) * pi / 180);
	// printf("resx : %f\n", res);
	return (res);
}

double find_end_y(int degree)
{
	double pi = 3.1415926535897932384626433832;
	double res = 0;
	res = 10 * cos((degree) * pi / 180);
	// printf("resy : %f\n", res);
	return (res * -1);
}

void ft_draw_line_dir(t_v *v, int y, int x, double degree, double i, int *tab)
{
	(void)y;
	double pi = 3.1415926535897932384626433832;
	// int degree = 270;
	double resultx = find_end_x(degree + i);
	double resulty = find_end_y(degree + i);
	// printf("resultx : %f et resulty : %f\n", resultx, resulty);
	double endx = ((x * XSIZE) + resultx);
	double endy = ((y * XSIZE) + resulty); // + pca on renvoie - ou + indifferement
	double deltax = endx - (x * XSIZE) ;
	double deltay = endy - (y * XSIZE);
	double pixelx = (x * XSIZE) + (XSIZE / 2);
	double pixely = (y * XSIZE) + (XSIZE / 2);
	// printf("endx=%f, endy=%f, deltax=%f, deltay=%f, pixelx=%f et pixely=%f\n", endx, endy, deltax, deltay, pixelx, pixely);
	// exit(0);
	int pixels = sqrt((deltax * deltax) + (deltay * deltay));
	deltax /= pixels;
	deltay /= pixels;
	printf("degree %f, i %f, (degree + i) %f\n", degree, i, (degree + i));
	double view = 30 - i; ;
	if (view < 0)
		view *= -1;
	while (1)
	{
		if (v->m.map[(int)pixely / XSIZE][(int)pixelx / XSIZE] == '1')
		{
			printf("(y * XSIZE) %i, pixely %f\n", (y * XSIZE), pixely);
			*tab = ((y * XSIZE) - pixely) * sin((90) * pi / 180) / sin((180 - 90 - (view)) * pi / 180);
			printf("view = %f, *tab %d\n", view, *tab);
			*tab = *tab * cos((view) * pi / 180);
			printf("*tab %d\n", *tab);
			return ;
		}
		ft_my_mlx_pixel_put(&v->ig, pixely, pixelx, ft_rgb_to_int(0, 50, 150, 250));
		pixelx += deltax;
		pixely += deltay;
	}
}

void	ft_draw_line_circle(t_v *v, int y, int x)
{
	
	double degree = 0;
	int right = degree + 30;
	int left = degree - 30;
	double i = 0.0;
	int index = 0;
	
	int tab[360];
	if (left < 0)
		left = 360 + left;
	if (right > 360)
		right = right - 360;
	while(index <= 360)
	{
		ft_draw_line_dir(v, y, x, left,  i, &tab[index]);
		printf("tab[%d] : %d\n", index, tab[index]);
		i = i + 0.16666666666;
		index++;
		if ((left + i) > 360)
			left = -30;
	}
	int z = 0;
	index = 0;
	while(index <= 360)
	{
		tab[index] = ((v->m.y * XSIZE) - (2 * XSIZE) - tab[index]);
		printf(" v->m.y %d, tab[index] %d, z %d\n", v->m.y * XSIZE, tab[index], z);
		while(z <= tab[index])
		{
			printf("int %d\n", ((v->m.y * XSIZE / 2) - (tab[index] / 2) + z));
			ft_my_mlx_pixel_put(&v->ig, ((v->m.y * XSIZE / 2) - (tab[index] / 2) + z) , (index + 100), \
			ft_rgb_to_int(0, 255, 0, 255));
			z++;
		}
		// break ;
		z = 0;
		index++;
	}	
}

void	ft_paint_map(t_v *v, int y, int x)
{
	int	i;
	int	j;

	i = 0;
	while (i < XSIZE)
	{
		j = 0;
		while (j < XSIZE)
		{
			if (j != 0)
			{
				ft_my_mlx_pixel_put(&v->ig, (y * XSIZE) + i, (x * XSIZE) + j, \
				ft_rgb_to_int(0, 255, 255, 255));
			}
			j++;
		}
		i++;
	}
}

void	ft_paint_player(t_v *v, int y, int x)
{
	int	i;
	int	j;
	int dif;
	int dif2;
	int ref;

	i = 0;
	dif = 32;
	dif2 = 32;
	ref = 0;
	while (i < XSIZE)
	{
		j = 0;
		while (j < XSIZE)
		{
			if (j != 0)
			{
				if ((i > ((XSIZE / 3) - 1) && i < (((XSIZE / 3) * 2) + 1)) && (j > ((XSIZE / 3) - 1) && j < (((XSIZE / 3) * 2) + 2)))
				{
					if (i % 2 == 0 && ref == i)
					{
						dif++;
						dif2--;
						ref = 0;
					}
					if (j >= dif2 && j <= dif)
					{
						ft_my_mlx_pixel_put(&v->ig, (y * XSIZE) + i, (x * XSIZE) + j, \
						ft_rgb_to_int(0, 255, 255, 255));
					}
				}
			}
			j++;
		}
		i++;
		ref = i;
	}
}

void	ft_check_map(t_v *v)
{
	int i;
	int j;

	i = 0;
	if (!v->m.map)
		return ;
	// ft_paint_map(v, 2, 2);
	while (v->m.map[i])
	{
		j = 0;
		while (v->m.map[i][j])
		{
			// ft_printf("v->m.map[%d][%d]=%c\n", i, j, v->m.map[i][j]);
			if (v->m.map[i][j] == '1')
				ft_paint_map(v, i, j);
			if (v->m.map[i][j] == 'P')
			{
				ft_draw_line_circle(v, i, j);
				ft_paint_player(v, i, j);
				// ft_draw_line_angle_right(v, i, j);
				// ft_draw_line_angle_left(v, i, j);
				
			}
			j++;
		}
		ft_printf("\n");
		i++;
	}
}

// void	ft_draw_ratio(t_v *v, t_data sprite, int y, int x)
// {
// 	double		i;
// 	double		j;
// 	int			color;
// 	double		ratio;

// 	j = 0;
// 	ratio = ((double)sprite.w / (double)(((v->m.y) * v->m.x)));
// 	y = y - (((v->m.y) * v->m.x) / 2);
// 	x = x - (((v->m.y) * v->m.x) / 2);
// 	while (j < (double)((v->m.y) * v->m.x))
// 	{
// 		i = 0;
// 		while (i < (double)((v->m.y) * v->m.x))
// 		{
// 			color = ft_get_color(&sprite, i * ratio, j * ratio);
// 			if (color != 0x000000FF)
// 				ft_my_mlx_pixel_put(&v->ig, (y + i), (x + j), color);
// 			i++;
// 		}
// 		j++;
// 	}
// }

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
		// ft_printf("var->m.map[i]=%s", var->m.map[i]);
		i++;
	}
	ft_printf("\n");
	var->m.y = i; // H
	var->m.x = ft_strlen(var->m.map[0]) - 1; // W
}

void	ft_init_mlx(t_v *var)
{
	var->mlx = mlx_init();
	if (!var->mlx)
		return (exit(1));
	ft_printf("var->m.y=%d et var->m.x=%d\n", var->m.y, var->m.x);
	var->win = mlx_new_window(var->mlx, ((var->m.x) * XSIZE), (var->m.y * XSIZE), "cub3D");
	if (!var->win)
		return (mlx_destroy_display(var->mlx), free(var->mlx), exit(1));
	var->ig.img = mlx_new_image(var->mlx, ((var->m.x) * XSIZE), (var->m.y * XSIZE));
	if (!var->ig.img)
		ft_stop_all(var, 1);
	var->ig.ad = mlx_get_data_addr(var->ig.img, &var->ig.bpp, &var->ig.llen, &var->ig.en);
	mlx_hook(var->win, 2, 1L << 0, ft_keypress_event, var);
	mlx_hook(var->win, 17, 1L << 17, ft_close_event, var);
	ft_draw_line_map(var);
	ft_check_map(var);
	mlx_put_image_to_window(var->mlx, var->win, var->ig.img, 0, 0);
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
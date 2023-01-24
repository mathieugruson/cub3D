/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 10:54:34 by mgruson           #+#    #+#             */
/*   Updated: 2023/01/24 19:15:29 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include "libs/libft/includes/libft.h"
# include "libs/libft/includes/ft_printf.h"
# include "libs/libft/includes/get_next_line.h"
# include "libs/minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>

# define X_3D 960
# define Y_3D 600

typedef struct s_raycast
{
	/* ft_display_3d.c */
	int y;
	int x;
	int right;
	int index;
	double left;
	double i;
	double printy;
	double	tab[960];
	char	dir[960];
	double	texture[960];

	/* ft_ray_cast.c */
	double resultx;
	double resulty;
	double pixely;
	double pixelx;
	int pixels;
	
}	t_raycast;

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
	double	ppx;
	double	ppy;
	int		degree;
	int		degree_status;
	double	resultx;
	double	resulty;
	double	resultx2;
	double	resulty2;
	double	pixelx;
	double	pixely;
	double	ppxux;
	double	ppyuy;
	double	ppxrx;
	double	ppyry;
	double	ppxlx;
	double	ppyly;
	int 	pixels;
	int 	dir;
}	t_map;

typedef struct s_var
{
	void	*mlx;
	void	*win;
	void	*mlx2;
	void	*win2;
	t_data	ig;
	t_data	ig2;
	t_data	walle;
	t_data	walln;
	t_data	walls;
	t_data	wallw;
	t_map	m;
}	t_v;

#define XSIZE 64

/* cub3d.c */
void	ft_my_mlx_pixel_put(t_data *data, int i, int j, int color);
unsigned int	ft_get_color(t_data *data, int x, int y);
int	ft_rgb_to_int(int t, int r, int g, int b);
double	find_end_x(double degree);
double	find_end_y(double degree);
int		ft_close_event(t_v *v);
void	ft_reset_paint(t_v *v, int y, int x);
void	ft_paint_player_pixel(t_v *v, int y, int x);
void	ft_draw_line_circle(t_v *v, int y, int x);
void	ft_draw_pix_line_circle(t_v *v, double y, double x);
void	ft_check_map(t_v *v);
void	ft_check_pix_map(t_v *v);
void	ft_draw_line_map(t_v *v);
void	ft_stop_all(t_v *v, int exint);
void	ft_draw_pix_line_dir(t_v *v, double y, double x, int degree);
void	ft_new_player_pos(t_v *v, double y, double x, int degree);

/* moove.c */
void	moove_player(int dir, t_v *v);
int		ft_keypress_event(int key, t_v *v);
double	find_wall_x(double degree);
double	find_wall_y(double degree);
void	ft_moove_display(t_v *v);
int		ft_moove_player(t_v *v, int degree);
int		ft_moove_ray(t_v *v, int sense);

/* display3d.c */
void ft_ray_cast(t_v *v, int y, int x, double degree, double i, double *tab, char *dir, double *texture);
void	ft_display_3d(t_v *v, int y, int x);

#endif


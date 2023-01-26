/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 10:54:34 by mgruson           #+#    #+#             */
/*   Updated: 2023/01/26 20:12:30 by mgruson          ###   ########.fr       */
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
	void		*img;
	char		*ad;
	int			pos;
	int			addr_use;
	int			bpp;
	int			llen;
	int			en;
	int			x;
	int			y;

}	t_data;

typedef struct s_map
{
	char		**map;
	int			x;
	int			y;
	int			px;
	int			py;
	double		ppx;
	double		ppy;
	int			degree;
	double		resultx;
	double		resulty;
	double		pixelx;
	double		pixely;
	int 		pixels;
}	t_map;

typedef struct s_var
{
	void	*mlx;
	void	*win;
	char		**args;
	char		pos;
	long int	valfrgb[3];
	long int	valcrgb[3];
	char		*valf;
	char		*valc;
	char		*valno;
	char		*valso;
	char		*valwe;
	char		*valea;
	t_data	ig2;
	t_data	ig3;
	t_data	walle;
	t_data	walln;
	t_data	walls;
	t_data	wallw;
	t_map	m;
}	t_v;

typedef struct s_index
{
	int i;
	int j;
	int k;
}	t_index;

#define XSIZE 64

/* cub3d.c */
void	ft_my_mlx_pixel_put(t_data *data, int i, int j, int color);
void	ft_clean_map(t_v *v, int i);
unsigned int	ft_get_color(t_data *data, int x, int y);
int		ft_rgb_to_int(int t, int r, int g, int b);
int		ft_tablen(char **str);
double	find_end_x(double degree);
double	find_end_y(double degree);
int		ft_close_event(t_v *v);
void	ft_reset_paint(t_v *v, int y, int x);
void	ft_paint_player_pixel(t_v *v, int y, int x);
void	ft_draw_line_circle(t_v *v, int y, int x);
void	ft_check_map(t_v *v);
void	ft_check_pix_map(t_v *v);
void	ft_draw_line_map(t_v *v);
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

/* ft_display3d.c */
void	ft_draw_wall_ratio(t_v *v, t_data d, t_raycast *rc);
void	ft_draw_texture_and_floor(t_v *v, t_raycast *rc);
void	init_raycast_value(t_v *v, t_raycast *rc);
void	ft_display_3d(t_v *v, int y, int x);

/* ft_raycast.c */

void	find_diry(t_v *v, double pixely, double pixelx, char *dir);
void	find_dirx(t_v *v, double pixely, double pixelx, char *dir);
void	collect_raycat_value_y(t_v *v, t_raycast *rc, int y, int x);
void	collect_raycat_value_x(t_v *v, t_raycast *rc, int y, int x);
int		ft_ray_cast(t_v *v, int y, int x, t_raycast *rc);

/* map_init.c */
void	ft_fd_error(void);
void	ft_str_error(void);
int		ft_size_init_map(char *argv);
char	**ft_init_tmap(char *argv, int j);
int		ft_elements_map_control(t_v *v);
int		ft_parsing_map(char *argv, t_v *v);
int		ft_start_position(t_v *v);

/* map_checker1.c */

int		ft_invasion_checker_condition(t_v *v, int x, int y, char c);
int		ft_invasion_checker(t_v *v, char c);
void	ft_invasion_loop_checker(t_v *v, int x, int y, char c);

/* map_checker2.c */

int	check_final_wall_part_2(t_v *v, int i, int x, int y);
int		check_final_wall(t_v *v, char c);
int		ft_invasion_loop(t_v *v, char c);
void	ft_argv_check(char *argv);

/* map_attack.c */

void	propagate_player(t_v *v, int tx, int ty, char c);
void	ft_west_offensive(int x, int y, t_v *v, char c);
void	ft_north_offensive(int x, int y, t_v *v, char c);
void	ft_east_offensive(int x, int y, t_v *v, char c);
void	ft_south_offensive(int x, int y, t_v *v, char c);
int		ft_invasion_propagation(int x, int y, t_v *v, char c);

/* ft_init_sprites.c */

void	ft_init_sprites_north_south(t_v *v);
void	ft_init_sprites_est_west(t_v *v);
void	ft_init_sprites(t_v *v);

/* ft_init_map_value.c */

void	init_each_value_of_map(t_v *v, int i, int j);
void	ft_init_map_value(t_v *v);

/* color.c */

void	ft_my_mlx_pixel_put(t_data *data, int i, int j, int color);
unsigned int	ft_get_color(t_data *data, int x, int y);
int	ft_rgb_to_int(int t, int r, int g, int b);
int	get_valrgb(t_v *v, char **tmp, char c);

/* ft_init.c */

int	ft_size_init_map(char *argv);
char	**ft_init_tmap(char *argv, int j);
void	init_window_and_image(t_v *var);
void	ft_init_mlx(t_v *var);
void	init_degree(t_v *var);
void	ft_init_data(t_v *var);
void	init_max_map_size(t_v *v);

/* ft_draw_line_map.c */

void	draw_line_mini_map(t_v *v, int i, int j);
void	ft_draw_line_map(t_v *v);
void	ft_paint_map(t_v *v, int y, int x);
void	ft_draw_player_dir(t_v *v, int degree);
void	ft_paint_player_pixel(t_v *v, int y, int x);

/* ft_check_display_map.c */

void	ft_check_pix_map(t_v *v);
void	ft_check_map(t_v *v);

/* ft_clean.c */

void	ft_clean_tstr(char **str, int i);

/* cub3d_utils.c */

int	ft_tablen(char **str);
char	**ft_tabdup(char **str);
char	**get_tmp_split(char **tmp, char *str);
void	ft_split_tostr(char **tab, char *str);
long int	ft_onlydigit_atoi(const char *nptr);

/* ft_control.c */

int	control_final_map(t_v *v);
int	ft_control_maparg(char *str);
int	control_map(t_v *v);

/* ft_check_arg.c */

int	ft_check_maparg(char *str);
void	check_in_color_arg(t_v *v, char *str);
int	ft_check_color_arg(char *str, char c, t_v *v);
int	ft_check_dir_arg(char *str, char c1, char c2);
void check_add_dir(char *str, int *j, t_v *v);
int	ft_check_argnbr(char **str);
int	check_color_format(char *str, char c, t_v *v);
int	ft_check_argcolor(char **str, t_v *v);
int	ft_check_argdir(char **str, t_v *v);

/* ft_error.c */

void	ft_fd_error(void);
void	ft_str_error(void);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chillion <chillion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 18:21:46 by chillion          #+#    #+#             */
/*   Updated: 2023/01/25 19:30:30 by chillion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_exit_map(t_v *v, int i)
{
	ft_clean_map(v, i);
	exit(EXIT_FAILURE);
}

void	ft_fd_error(void)
{
	ft_printf("Error\n%s\n", strerror(errno));
	exit(EXIT_FAILURE);
}

void	ft_str_error(void)
{
	ft_printf("Error\nEmpty map file\n");
	exit(EXIT_FAILURE);
}

int	ft_size_init_map(char *argv)
{
	int				fd;
	long int		i;
	char			*str;

	fd = open(argv, O_RDONLY);
	if (fd == -1)
		ft_fd_error();
	i = 0;
	str = get_next_line(fd);
	if (!str)
		ft_str_error();
	while (str)
	{
		free(str);
		str = get_next_line(fd);
		i++;
	}
	fd = close(fd);
	if (i > 2147483647)
		i = -1;
	return ((int)i);
}

char	**ft_init_tmap(char *argv, int j)
{
	int	fd;
	int	i;

	(void)j;
	fd = open(argv, O_RDONLY);
	if (fd == -1)
		ft_fd_error();
	i = 0;
	char **tmp;
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

int	ft_ctrl_map_size(t_v *v, int i)
{
	// ft_map_width_height(v);
	while (v->m.map[i])
		i++;
	if (i < 3)
	{
		errno = 22;
		perror("Error\nMap size is not correct ");
		// ft_exit_map(v, i);
	}
	return (i);
}

int	ft_elements_map_control(t_v *v)
{
	int		j;
	int		k;
	char	error;

	j = 1;
	error = 0;
	while (v->m.map[j + 1])
	{
		k = 1;
		while (v->m.map[j][k + 1])
		{
			if (v->m.map[j][k] != '1' && v->m.map[j][k] != '0'
				&& v->m.map[j][k] != 'P' && v->m.map[j][k] != 'E'
					&& v->m.map[j][k] != 'C')
			{
				error = v->m.map[j][k];
				break ;
			}
			k++;
		}
		j++;
	}
	if (error != 0)
		ft_printf("Error\nFIND UNKNOWN ELEMENT (%c) ON MAP\n", error);
	return (error);
}

int	ft_contour_map_control(t_v *v, int i)
{
	int	j;
	int	k;
	int	error;

	j = 0;
	error = 0;
	while (v->m.map[j])
	{
		k = 0;
		while (v->m.map[j][k + 1])
		{
			if (v->m.map[0][k] != '1' || v->m.map[i - 1][k] != '1'
				|| v->m.map[j][0] != '1')
				error += 1;
			k++;
		}
		j++;
	}
	if (error != 0)
		ft_printf("Error\nMAP NOT ENCLOSE BY WALLS : %s\n", strerror(22));
	return (error);
}

void	ft_print_tab(char **str)
{
	int i;

	i = 0;
	if (!str)
		return ;
	while(str[i])
	{
		ft_printf("%s", str[i]);
		i++;
	}
}

void	ft_clean_tstr(char **str, int i)
{
	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		if (str[i])
			free(str[i]);
		i++;
	}
	if (str)
		free(str);
}

int	ft_check_maparg(char *str)
{
	int i;
	int k;

	i = 0;
	k = ft_strlen(str);
	if (k < 2)
		return (1);
	while(str[i])
	{
		if (str[i] != '1' && str[i] != '0' && str[i] != 'N' && str[i] != ' ' \
		&& str[i] != 'S' && str[i] != 'E' && str[i] != 'W'&& str[i] != '\n')
			return(1);
		i++;
	}
	return (0);
}

int	ft_tablen(char **str)
{
	int i;

	i = 0;
	if (!str)
		return(0);
	while(str[i])
		i++;
	return (i);
}

void	ft_split_tostr(char **tab, char *str)
{
	int i;
	int j;
	int k;
	
	i = 0;
	j = 0;
	k = 0;
	while(tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			str[j + k] = tab[i][j];
			j++;
		}
		k = k + j;
		if (tab[i + 1])
		{
			str[k] = ' ';
			k++;
		}
		i++;
	}
	str[k] = '\0';
}

int	ft_check_color_arg(char *str, char c)
{
	int i;
	int k;
	char **tmp;

	i = 0;
	tmp = NULL;
	k = ft_strlen(str);
	if (k < 2)
		return (1);
	if (str[0] != c)
		return(1);
	while(str[i])
	{
		if (i != 0)
		{
			if (str[i] != ' ' && str[i] != ',' \
			&& str[i] != '\n' && ft_isdigit(str[i]) == 0)
			return(1);
		}
		i++;
	}
	tmp = ft_split(str, ' ');
	if (ft_tablen(tmp) != 2)
		return (ft_printf("Error\nValue of color arg unvailable\n"), ft_clean_tstr(tmp, 0), 1);
	ft_split_tostr(tmp, str);
	ft_clean_tstr(tmp, 0);
	return (0);
}

int	ft_check_dir_arg(char *str, char c1, char c2)
{
	int k;
	char **tmp;

	tmp = NULL;
	k = ft_strlen(str);
	if (k < 4)
		return (1);
	if (str[0] != c1 || str[1] != c2)
		return(1);
	tmp = ft_split(str, ' ');
	if (ft_tablen(tmp) != 2)
		return (ft_clean_tstr(tmp, 0), 1);
	ft_split_tostr(tmp, str);
	ft_clean_tstr(tmp, 0);
	return (0);
}

void check_add_dir(char *str, int *j, t_v *v)
{
	if (ft_check_dir_arg(str, 'N', 'O') == 0)
	{
		v->valno = str;
		(*j)++;
	}
	if (ft_check_dir_arg(str, 'S', 'O') == 0)
	{
		v->valso = str;
		(*j)++;
	}
	if (ft_check_dir_arg(str, 'W', 'E') == 0)
	{
		v->valwe = str;
		(*j)++;
	}
	if (ft_check_dir_arg(str, 'E', 'A') == 0)
	{
		v->valea = str;
		(*j)++;
	}
}

int	ft_check_argnbr(char **str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while(str[i])
	{
		if (ft_check_maparg(str[i]) == 1)
			j++;
		i++;
	}
	if (j < 7)
		return(ft_printf("Error\nNumber of arguments unvailable\n"), 1);
	return (0);
}

long int	ft_onlydigit_atoi(const char *nptr)
{
	int			x;
	long int	nb;

	x = 0;
	nb = 0;
	if (!nptr[x])
		return (999999999999);
	while ((nptr[x] >= '0' && nptr[x] <= '9') && nptr[x] != '\0')
	{
		nb = nb * 10 + (nptr[x] - 48);
		x++;
	}
	if ((nb > 255) || (nb < 0) || !nptr[0])
		return (999999999999);
	if (nptr[x] == '\n')
	{
		if (nptr[x + 1] != '\0')
			return (999999999999);
	}
	return (nb);
}

int	check_color_format(char *str, char c, t_v *v)
{
	int	i;
	int j;
	char **tmp;

	i = 0;
	j = 0;
	while(str[i])
	{
		if (str[i] == ',' && (ft_isdigit(str[i + 1]) != 0 || ft_isdigit(str[i - 1] != 0)))
			j++;
		i++;
	}
	if (j != 2)
		return (1);
	i = 0;
	while(str[i])
	{
		if (str[i] == ' ' && str[i + 1] != '\0')
		{
			i++;
			tmp = ft_split(str + i, ',');
			break ;
		}
		i++;
	}
	if (ft_tablen(tmp) != 3)
		return (ft_clean_tstr(tmp, 0), 1);
	i = 0;
	while(i < 3 && c == 'C')
	{
		v->valcrgb[i] = ft_onlydigit_atoi(tmp[i]);
		i++;
	}
	i = 0;
	while(i < 3 && c == 'F')
	{
		v->valfrgb[i] = ft_onlydigit_atoi(tmp[i]);
		i++;
	}
	ft_clean_tstr(tmp, 0);
	return (0);
}

int	ft_check_argcolor(char **str, t_v *v)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while(str[i])
	{
		if (ft_check_color_arg(str[i], 'F') == 0)
		{
			v->valf = str[i];
			j++;
		}
		if (ft_check_color_arg(str[i], 'C') == 0)
		{
			v->valc = str[i];
			j++;
		}
		i++;
	}
	if (j != 2)
		return(ft_printf("Error\nNumber of color arguments is wrong\n"), 1);
	j = check_color_format(v->valf, 'F', v);
	j = j + check_color_format(v->valc, 'C', v);
	if (j != 0)
		return(ft_printf("Error\nFormat of color arguments is wrong\n"), 1);
	return (0);
}

int	ft_check_argdir(char **str, t_v *v)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while(str[i])
	{
		check_add_dir(str[i], &j, v);
		i++;
	}
	if (j != 4)
		return(ft_printf("Error\nNumber of texture arguments is wrong\n"), 1);
	return (0);
}


int	begin_map(char *str, int *j)
{
	int i;
	int k;

	i = 0;
	k = 0;
	if ((*j) != 0)
		return (0);
	while(str[i])
	{
		if (ft_strlen(str) < 2)
			return (1);
		if (str[i] != '1' && str[i] != ' ' && str[i] != '\n')
			return (1);
		if (str[i] == '1')
			k++;
			
		i++;
	}
	if (str[i - 1] != '\n' || k < 1)
		return (1);
	return (0);
}

int	ft_keep_map_only(char **str, t_v *v)
{
	int i;
	int j;
	char **tmp;

	i = 5;
	j = 0;
	while(str[i])
	{
		if (begin_map(str[i], &j) == 0)
		{
			if (j == 0)
				j = i;
		}
		i++;
	}
	tmp = (char **)malloc(sizeof(char *) * (i + 1));
	if (!tmp)
		return (1);
	i = 0;
	while (str[j + i])
	{
		tmp[i] = str[j + i];
		str[j + i] = '\0';
		i++;
	}
	tmp[i] = '\0';
	v->m.map = tmp;
	return (0);
}

int	ft_start_position(t_v *v)
{
	int i;
	int j;
	int k;

	if (!v->m.map)
		return (1);
	i = 0;
	j = 0;
	k = 0;
	while (v->m.map[i])
	{
		j = 0;
		while(v->m.map[i][j])
		{
			if (v->m.map[i][j] == 'N' || v->m.map[i][j] == 'S' \
			|| v->m.map[i][j] == 'E' || v->m.map[i][j] == 'W')
			{
				v->pos = v->m.map[i][j];
				k++;
			}
			if (k > 1)
				return (ft_printf("Error\nToo much player position on map\n"), 1);
			j++;
		}
		i++;
	}
	if (k == 0)
		return (ft_printf("Error\nNo player position on map\n"), 1);
	return(0);
}

char	**ft_tabdup(char **str)
{
	int i;
	char	**tmp;

	if (!str)
		return (NULL);
	i = ft_tablen(str);
	tmp = (char **)malloc(sizeof(char *) * (i + 1));
	if (!tmp)
		return (NULL) ;
	tmp[i] = 0;
	i = 0;
	while(str[i])
	{
		tmp[i] = ft_strdup(str[i]);
		i++; 
	}
	return (tmp);
}

int	control_final_map(t_v *v)
{
	int		i;
	char	**tmp;

	if (!v->m.map)
		return (1);
	i = 0;
	v->pos = 'A';
	while (v->m.map[i])
	{
		if (ft_strlen(v->m.map[i]) < 2 || ft_check_maparg(v->m.map[i]))
			return (ft_printf("Error\nUnvailable value on map part\n"), 1);
		if (v->m.map[i][0] != '1' && v->m.map[i][0] != ' ')
			return(ft_printf("Error\nMap is not close by wall\n"), 1);
		i++;
	}
	ft_start_position(v);
	if (v->pos == 'A')
		return (1);
	tmp = ft_tabdup(v->m.map);
	if (ft_invasion_loop(v, v->pos))
		return (1);
	ft_clean_tstr(v->m.map, 0);
	v->m.map = tmp;
	ft_print_tab(v->m.map);
	return (0);
}

int	ft_control_maparg(char *str)
{
	int i;
	int k;
	char **tmp;

	i = 0;
	k = ft_strlen(str);
	if (k < 1)
		return (1);
	if (str[i] != 'N' && str[i] != 'S' && str[i] != 'W' \
	&& str[i] != ' ' && str[i] != 'E' && str[i] != 'F' \
	&& str[i] != 'C' && str[i] != '\n' && str[i] != '1')
		return(1);
	while (str[i])
	{
		tmp = ft_split(str, ' ');
		if (ft_tablen(tmp) < 1)
			return (ft_clean_tstr(tmp, 0), 1);
		if (tmp[0][0] != 'N' && tmp[0][0] != 'S' && tmp[0][0] != 'W' \
		&& tmp[0][0] != ' ' && tmp[0][0] != 'E' && tmp[0][0] != 'F' \
		&& tmp[0][0] != 'C' && tmp[0][0] != '\n' && tmp[0][0] != '1')
			return (ft_clean_tstr(tmp, 0), 1);
		ft_clean_tstr(tmp, 0);
		i++;
	}
	return (0);
}

int	control_map(t_v *v)
{
	int i;

	if (!v->args)
		return (1);
	i = 0;
	while (v->args[i])
	{
		if (ft_control_maparg(v->args[i]))
			return (ft_printf("Error\nUnvailable value on map part\n"), 1);
		i++;
	}
	ft_printf("REPAIRError\n\n");
	return (0);
}

int	ft_parsing_map(char *argv, t_v *v)
{
	int		i;
	int		j;

	(void)v;
	i = 0;
	v->m.map = NULL;
	v->args = NULL;
	j = ft_size_init_map(argv);
	if (j == -1)
		return (ft_printf("Error\nFile map is too big for int parsing\n") \
		, exit(EXIT_FAILURE), 1);
	if (j < 5)
		return (ft_printf("Error\nFile map is too big for int parsing\n") \
		, exit(EXIT_FAILURE), 1);
	v->args = ft_init_tmap(argv, j);
	
	ft_print_tab(v->args);
	if (control_map(v) == 1)
		return (1);
	if (ft_check_argnbr(v->args) || ft_check_argdir(v->args, v) \
	|| ft_check_argcolor(v->args, v))
		return (ft_clean_tstr(v->args, 0), exit(EXIT_FAILURE), 1);
	ft_printf("[%s]\n",v->valf);
	ft_printf("[%s]\n",v->valc);
	ft_printf("[%s]\n",v->valno);
	ft_printf("[%s]\n",v->valso);
	ft_printf("[%s]\n",v->valwe);
	ft_printf("[%s]\n",v->valea);
	ft_printf("[%d]\n",v->valcrgb[0]);
	ft_printf("[%d]\n",v->valcrgb[1]);
	ft_printf("[%d]\n",v->valcrgb[2]);
	ft_printf("[%d]\n",v->valfrgb[0]);
	ft_printf("[%d]\n",v->valfrgb[1]);
	ft_printf("[%d]\n",v->valfrgb[2]);
	ft_keep_map_only(v->args, v);
	ft_printf("GGGGGGGG\n");
	ft_print_tab(v->args);
	ft_printf("BBBBBBBB\n");
	ft_print_tab(v->m.map);
	if (control_final_map(v))
		return (ft_clean_tstr(v->m.map, 0), ft_clean_tstr(v->args, 0), exit(EXIT_FAILURE), 1);
	ft_print_tab(v->m.map);
	i = 0;
	int k = 0;
	while(v->m.map[i])
	{
		j = ft_strlen(v->m.map[i]);
		if (j > k)
			k = j;
		i++;
	}
	v->m.y = ft_tablen(v->m.map); // H
	v->m.x = k;
	ft_printf("v->m.y=%d et v->m.x=%d\n", v->m.y, v->m.x);
	ft_printf("VVVVVVVV\n");
	// free(v->valf);
	// free(v->valc);
	// free(v->valno);
	// free(v->valso);
	// free(v->valwe);
	// free(v->valea);
	// i = ft_ctrl_map_size(v, i);
	// if (ft_contour_map_control(v, i) != 0 || ft_elements_map_control(v) != 0
	// 	|| ft_control_its(v) == 0 || ft_invasion_loop(v))
	// 	ft_exit_map(v, i);
	// ft_clean_map(v, i);
	return (i);
}
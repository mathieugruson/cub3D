/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 18:21:46 by chillion          #+#    #+#             */
/*   Updated: 2023/01/26 20:10:51 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	begin_map(char *str, int *j)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	if ((*j) != 0)
		return (0);
	while (str[i])
	{
		if (ft_strlen(str) < 2)
			return (1);
		if (str[i] != '1' && str[i] != '0' && str[i] != ' ' && str[i] != '\n')
			return (1);
		if (str[i] == '1' || str[i] == '0')
			k++;
		i++;
	}
	if (str[i - 1] != '\n' || k < 1)
		return (1);
	return (0);
}

int	ft_keep_map_only(char **str, t_v *v)
{
	int		i;
	int		j;
	char	**tmp;

	i = 5;
	j = 0;
	while (str[i])
	{
		if (begin_map(str[i], &j) == 0 && (j == 0))
			j = i;
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

static int	check_str(t_v *v, int i, int j)
{
	if (v->m.map[i][j] == 'N' || v->m.map[i][j] == 'S' \
	|| v->m.map[i][j] == 'E' || v->m.map[i][j] == 'W')
		return (1);
	return (0);
}

int	ft_start_position(t_v *v)
{
	t_index	i;

	if (!v->m.map)
		return (1);
	i.i = 0;
	i.k = 0;
	while (v->m.map[i.i])
	{
		i.j = 0;
		while (v->m.map[i.i][i.j])
		{
			if (check_str(v, i.i, i.j))
			{
				v->pos = v->m.map[i.i][i.j];
				i.k++;
			}
			if (i.k > 1)
				return (ft_printf("Error\nToo much player on map\n"), 1);
			i.j++;
		}
		i.i++;
	}
	if (i.k == 0)
		return (ft_printf("Error\nNo player position on map\n"), 1);
	return (0);
}

int	ft_parsing_map(char *argv, t_v *v)
{
	int		j;

	v->m.map = NULL;
	v->args = NULL;
	j = ft_size_init_map(argv);
	if (j == -1)
		return (ft_printf("Error\nFile map is too big for int parsing\n") \
		, ft_close_event(v), 1);
	if (j < 5)
		return (ft_printf("Error\nNot enough informations to start\n") \
		, ft_close_event(v), 1);
	v->args = ft_init_tmap(argv, j);
	if (control_map(v) == 1)
		return (ft_close_event(v), 1);
	if (ft_check_argnbr(v->args) || ft_check_argdir(v->args, v) \
	|| ft_check_argcolor(v->args, v))
		return (ft_close_event(v), 1);
	ft_keep_map_only(v->args, v);
	if (control_final_map(v))
		return (ft_close_event(v), 1);
	init_max_map_size(v);
	return (0);
}

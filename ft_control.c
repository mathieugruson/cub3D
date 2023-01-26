/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_control.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 18:44:37 by mgruson           #+#    #+#             */
/*   Updated: 2023/01/26 20:01:24 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		i++;
	}
	if (ft_start_position(v))
		return (ft_close_event(v), 1);
	if (v->pos == 'A')
		return (1);
	tmp = ft_tabdup(v->m.map);
	if (ft_invasion_loop(v, v->pos))
		return (ft_clean_tstr(tmp, 0), 1);
	ft_clean_tstr(v->m.map, 0);
	v->m.map = tmp;
	return (0);
}

int	check_string(char *str, int i)
{
	if (str[i] != 'N' && str[i] != 'S' && str[i] != 'W' && str[i] != ' ' \
	&& str[i] != 'E' && str[i] != 'F' && str[i] != 'C' && str[i] != '\n' \
	&& str[i] != '1' && str[i] != '0')
		return (1);
	return (0);
}

int	ft_control_maparg(char *str)
{
	int		i;
	int		k;
	char	**tmp;

	i = 0;
	tmp = NULL;
	k = ft_strlen(str);
	if (k < 1)
		return (1);
	if (check_string(str, i))
		return (1);
	while (str[i])
	{
		tmp = ft_split(str, ' ');
		if (ft_tablen(tmp) < 1)
			return (ft_clean_tstr(tmp, 0), 1);
		if (tmp[0][0] != 'N' && tmp[0][0] != 'S' && tmp[0][0] != 'W' \
		&& tmp[0][0] != ' ' && tmp[0][0] != 'E' && tmp[0][0] != 'F' \
		&& tmp[0][0] != 'C' && tmp[0][0] != '\n' && tmp[0][0] != '1' \
		&& tmp[0][0] != '0')
			return (ft_clean_tstr(tmp, 0), 1);
		ft_clean_tstr(tmp, 0);
		i++;
	}
	return (0);
}

int	control_map(t_v *v)
{
	int	i;

	if (!v->args)
		return (1);
	i = 0;
	while (v->args[i])
	{
		if (ft_control_maparg(v->args[i]))
			return (ft_printf("Error\nWrong formatting of map infos\n"), 1);
		i++;
	}
	return (0);
}

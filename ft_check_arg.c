/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 18:47:46 by mgruson           #+#    #+#             */
/*   Updated: 2023/01/26 19:55:27 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_add_dir(char *str, int *j, t_v *v)
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
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (ft_check_maparg(str[i]) == 1)
			j++;
		i++;
	}
	if (j < 6)
		return (ft_printf("Error\nNumber of arguments unvailable\n"), 1);
	return (0);
}

int	check_color_format(char *str, char c, t_v *v)
{
	int		i;
	int		j;
	char	**tmp;

	i = 0;
	j = 0;
	tmp = NULL;
	while (str[i])
	{
		if (str[i] == ',' && (ft_isdigit(str[i + 1]) != 0 || \
		ft_isdigit(str[i - 1] != 0)))
			j++;
		i++;
	}
	if (j != 2)
		return (1);
	tmp = get_tmp_split(tmp, str);
	if (ft_tablen(tmp) != 3 || get_valrgb(v, tmp, c) == 1)
		return (ft_clean_tstr(tmp, 0), 1);
	return (ft_clean_tstr(tmp, 0), 0);
}

int	ft_check_argcolor(char **str, t_v *v)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (ft_check_color_arg(str[i], 'F', v) == 0 && j++ > -1)
			v->valf = str[i];
		if (ft_check_color_arg(str[i], 'C', v) == 0 && j++ > -1)
			v->valc = str[i];
		i++;
	}
	if (j != 2)
		return (ft_printf("Error\nNumber of color arguments is wrong\n"), 1);
	j = check_color_format(v->valf, 'F', v);
	j = j + check_color_format(v->valc, 'C', v);
	if (j != 0)
		return (ft_printf("Error\nFormat of color arguments is wrong\n"), 1);
	return (0);
}

int	ft_check_argdir(char **str, t_v *v)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		check_add_dir(str[i], &j, v);
		i++;
	}
	if (j != 4)
		return (ft_printf("Error\nNumber of texture arguments is wrong\n"), 1);
	return (0);
}

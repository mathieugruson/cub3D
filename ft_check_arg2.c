/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_arg2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 19:53:15 by mgruson           #+#    #+#             */
/*   Updated: 2023/01/26 19:53:51 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_check_maparg(char *str)
{
	int	i;
	int	k;

	i = 0;
	k = ft_strlen(str);
	if (k < 2)
		return (1);
	while (str[i])
	{
		if (str[i] != '1' && str[i] != '0' && str[i] != 'N' && \
		str[i] != ' ' && str[i] != 'S' && str[i] != 'E' && str[i] != 'W' \
		&& str[i] != '\n')
			return (1);
		i++;
	}
	return (0);
}

void	check_in_color_arg(t_v *v, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (i != 0)
		{
			if (str[i] != ' ' && str[i] != ',' \
			&& str[i] != '\n' && ft_isdigit(str[i]) == 0)
				return (ft_printf("Error\nValue of color arg unvailable\n"), \
				ft_close_event(v), (void) 1);
		}
		i++;
	}
}

int	ft_check_color_arg(char *str, char c, t_v *v)
{
	int		k;
	char	**tmp;

	tmp = NULL;
	k = ft_strlen(str);
	if (k < 2)
		return (1);
	if (str[0] != c)
		return (1);
	check_in_color_arg(v, str);
	tmp = ft_split(str, ' ');
	if (ft_tablen(tmp) != 2 || ft_strlen(tmp[0]) != 1)
		return (ft_printf("Error\nValue of color arg unvailable\n"), \
		ft_clean_tstr(tmp, 0), ft_close_event(v), 1);
	ft_split_tostr(tmp, str);
	ft_clean_tstr(tmp, 0);
	return (0);
}

int	ft_check_dir_arg(char *str, char c1, char c2)
{
	int		k;
	char	**tmp;

	tmp = NULL;
	k = ft_strlen(str);
	if (k < 4)
		return (1);
	if (str[0] != c1 || str[1] != c2)
		return (1);
	tmp = ft_split(str, ' ');
	if (ft_tablen(tmp) != 2 || ft_strlen(tmp[0]) != 2)
		return (ft_clean_tstr(tmp, 0), 1);
	ft_split_tostr(tmp, str);
	ft_clean_tstr(tmp, 0);
	return (0);
}

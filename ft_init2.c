/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 20:26:32 by mgruson           #+#    #+#             */
/*   Updated: 2023/01/27 21:17:36 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_max_map_size(t_v *v)
{
	long int	i;
	long int	j;
	long int	k;

	j = 0;
	i = 0;
	k = 0;
	if (!v->m.map)
		return (1);
	while (v->m.map[i])
	{
		j = ft_strlen(v->m.map[i]);
		if (j > k)
			k = j;
		i++;
	}
	if (k > (INT_MAX / 64) || j > (INT_MAX / 64))
		return (1);
	v->m.y = ft_tablen(v->m.map);
	v->m.x = k;
	return (0);
}

int	ft_size_init_map(char *argv)
{
	int			fd;
	long int	i;
	char		*str;

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

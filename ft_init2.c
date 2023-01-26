/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 20:26:32 by mgruson           #+#    #+#             */
/*   Updated: 2023/01/26 20:27:48 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_max_map_size(t_v *v)
{
	int	i;
	int	k;
	int	j;

	j = 0;
	i = 0;
	k = 0;
	while (v->m.map[i])
	{
		j = ft_strlen(v->m.map[i]);
		if (j > k)
			k = j;
		i++;
	}
	v->m.y = ft_tablen(v->m.map);
	v->m.x = k;
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 18:33:08 by mgruson           #+#    #+#             */
/*   Updated: 2023/01/26 20:03:31 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_tablen(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	**ft_tabdup(char **str)
{
	int		i;
	char	**tmp;

	if (!str)
		return (NULL);
	i = ft_tablen(str);
	tmp = (char **)malloc(sizeof(char *) * (i + 1));
	if (!tmp)
		return (NULL);
	tmp[i] = 0;
	i = 0;
	while (str[i])
	{
		tmp[i] = ft_strdup(str[i]);
		i++;
	}
	return (tmp);
}

char	**get_tmp_split(char **tmp, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' && str[i + 1] != '\0' && i++ > -1)
		{
			tmp = ft_split(str + i, ',');
			break ;
		}
		i++;
	}
	return (tmp);
}

void	ft_split_tostr(char **tab, char *str)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (tab[i])
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

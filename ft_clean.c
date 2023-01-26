/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgruson <mgruson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 18:31:16 by mgruson           #+#    #+#             */
/*   Updated: 2023/01/26 18:43:35 by mgruson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	{
		free(str);
		str = NULL;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: himejjad <himejjad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 07:53:04 by himejjad          #+#    #+#             */
/*   Updated: 2023/10/29 17:00:49 by himejjad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void	check_wall2(t_args *args)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (args->copy[i][j])
	{
		if (args->copy[i][j] != '1' || args->copy[args->height - 1][j] != '1')
		{
			if (args->copy[i][j] == ' ' || args->copy[args->height - 1][j] == ' ')
				j++;
			else if (args->copy[i][j] == '0' || args->copy[args->height - 1][j] == '0')
			{
				// printf("=-=-=-=-=-=->%c\n", args->copy[i][j]);
				error();
			}
		}
		j++;
	}
	
	i++;
	while (i < args->height)
	{
        args->width = ft_strlen(args->copy[i]);
		if (args->copy[i][0] != '1'
		|| args->copy[i][args->width - 1] != '1' )
		{
			if (args->copy[i][0] == ' ' &&  args->copy[i][args->width - 1] == ' ')
				i++;
			else if (args->copy[i][0] == '0' ||  args->copy[i][args->width - 1] == '0')
			{
				// printf("=-=-=-=-=-=->%c\n", args->copy[i][0]);
				error();
			}
		}
		i++;
	}
}

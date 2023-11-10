/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utls_parse_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: himejjad <himejjad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 19:48:54 by himejjad          #+#    #+#             */
/*   Updated: 2023/11/10 19:59:42 by himejjad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	norm_space(t_args *args, int j, int i)
{
	if (args->copy[j][i] == '0')
	{
		if (args->copy[j + 1][i] == ' ')
			error();
		if (args->copy[j - 1][i] == ' ')
			error();
		if (args->copy[j][i + 1] == ' ')
			error();
		if (args->copy[j][i - 1] == ' ')
			error();
		i++;
	}
}

void	norm_skip_space(t_args *args, int j, int i)
{
	if (args->copy[j][i] >= 'A' && args->copy[j][i] <= 'Z')
	{
		if (args->copy[j][i] == 'W' || args->copy[j][i] == 'S'
			|| args->copy[j][i] == 'E' || args->copy[j][i] == 'N')
			i++;
		else
			error();
	}
	if (args->copy[j][i] == '0')
	{
		if (!args->copy[j + 1][i])
			error();
		else if (!args->copy[j - 1][i])
			error();
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utls_parse_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: himejjad <himejjad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 21:39:56 by himejjad          #+#    #+#             */
/*   Updated: 2023/11/10 19:54:07 by himejjad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_isalnum(int c)
{
	if (c == ' ')
		return (1);
	if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A'
			&& c <= 'Z'))
		return (1);
	return (0);
}

void	check_space_2(t_args *args)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (args->copy[j])
	{
		i = 0;
		while (args->copy[j][i])
		{
			norm_space(args, j, i);
			i++;
		}
		j++;
	}
}

void	skip_space(t_args *args)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (args->copy[j])
	{
		i = 0;
		while (args->copy[j][i])
		{
			if (args->copy[j][i] == '\t')
				i++;
			if (!ft_isalnum(args->copy[j][i]))
				error();
			if (args->copy[j][i] >= '2' && args->copy[j][i] <= '9')
				error();
			if (args->copy[j][i] >= 'a' && args->copy[j][i] <= 'z')
				error();
			norm_skip_space(args, j, i);
			i++;
		}
		j++;
	}
}

void	check_n_w_s_e(t_args *args)
{
	int	j;
	int	i;
	int	count;

	count = 0;
	j = 0;
	i = 0;
	while (args->copy[j])
	{
		i = 0;
		while (args->copy[j][i])
		{
			if (args->copy[j][i] == 'W' || args->copy[j][i] == 'N'
				|| args->copy[j][i] == 'S' || args->copy[j][i] == 'E')
				count++;
			i++;
		}
		j++;
	}
	if (count != 1)
		error();
}

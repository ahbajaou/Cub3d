/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utls_parse_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: himejjad <himejjad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 21:39:56 by himejjad          #+#    #+#             */
/*   Updated: 2023/11/09 21:48:53 by himejjad         ###   ########.fr       */
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

void	skip_norm_n(t_args *args, int j, int i, char c)
{
	args->copy[args->height] = malloc(sizeof(char *));
	args->copy[args->height] = ft_strdup("");
	if (args->copy[j][i + 1] == '0' || args->copy[j][i + 1] == c)
		error();
	else if (args->copy[j][i - 1] == '0' || args->copy[j][i - 1] == c)
		error();
	else if (args->copy[j + 1][i] == '0' || args->copy[j + 1][i] == c)
		error();
	if (j == 0)
		j--;
	else if (args->copy[j - 1][i] == '0' || args->copy[j - 1][i] == c)
		error();
}

void	skip_space_norm(t_args *args, int j, int i)
{
	if (args->copy[j][i] == '\t')
		i++;
	if (!ft_isalnum(args->copy[j][i]))
		error();
	if (args->copy[j][i] >= '2' && args->copy[j][i] <= '9')
		error();
	if (args->copy[j][i] >= 'a' && args->copy[j][i] <= 'z')
		error();
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
			skip_space_norm(args, j, i);
			if (args->copy[j][i] == ' ')
			{
				skip_norm_n(args, j, i, 'N');
				skip_norm_n(args, j, i, 'W');
				skip_norm_n(args, j, i, 'E');
				skip_norm_n(args, j, i, 'S');
				i++;
			}
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

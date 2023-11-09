/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utls_parse_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: himejjad <himejjad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 21:33:39 by himejjad          #+#    #+#             */
/*   Updated: 2023/11/09 21:48:19 by himejjad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_face_norm(t_args *args, int j, int i, int count)
{
	while (args->argv[j][i])
	{
		if (args->argv[j][i] == 'N' && args->argv[j][i + 1] == 'O'
			&& args->argv[j][i + 2] == ' ')
			count++;
		if (args->argv[j][i] == 'S' && args->argv[j][i + 1] == 'O'
			&& args->argv[j][i + 2] == ' ')
			count++;
		if (args->argv[j][i] == 'W' && args->argv[j][i + 1] == 'E'
			&& args->argv[j][i + 2] == ' ')
			count++;
		if (args->argv[j][i] == 'E' && args->argv[j][i + 1] == 'A'
			&& args->argv[j][i + 2] == ' ')
			count++;
		if (args->argv[j][i] == 'F' && args->argv[j][i + 1] == ' ')
			count++;
		if (args->argv[j][i] == 'C' && args->argv[j][i + 1] == ' ')
			count++;
		i++;
	}
	return (count);
}

void	check_face(t_args *args)
{
	int	j;
	int	i;
	int	count;

	j = 0;
	i = 0;
	count = 0;
	while (args->argv[j])
	{
		i = 0;
		count = check_face_norm(args, j, i, count);
		j++;
	}
	if (count != 6)
		error();
}

int	skip_space_2(t_args *args, int j, int i)
{
	int	n;

	n = 0;
	i += 2;
	while (args->argv[j][i] == ' ')
		i++;
	return (i);
}

void	get_deriction_norm(t_args *args, int j, int i)
{
	while (args->argv[j][i])
	{
		if (args->argv[j][i] == 'N' && args->argv[j][i + 1] == 'O')
			args->no = ft_substr(args->argv[j], skip_space_2(args, j, i),
					ft_strlen(args->argv[j]));
		if (args->argv[j][i] == 'S' && args->argv[j][i + 1] == 'O')
			args->so = ft_substr(args->argv[j], skip_space_2(args, j, i),
					ft_strlen(args->argv[j]));
		if (args->argv[j][i] == 'W' && args->argv[j][i + 1] == 'E')
			args->we = ft_substr(args->argv[j], skip_space_2(args, j, i),
					ft_strlen(args->argv[j]));
		if (args->argv[j][i] == 'E' && args->argv[j][i + 1] == 'A')
			args->ea = ft_substr(args->argv[j], skip_space_2(args, j, i),
					ft_strlen(args->argv[j]));
		if (args->argv[j][i] == 'F')
			args->floor = ft_substr(args->argv[j], skip_space_2(args, j, i - 1),
					ft_strlen(args->argv[j]));
		if (args->argv[j][i] == 'C')
			args->cell = ft_substr(args->argv[j], skip_space_2(args, j, i - 1),
					ft_strlen(args->argv[j]));
		i++;
	}
}

void	get_deriction(t_args *args)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	while (args->argv[j])
	{
		i = 0;
		get_deriction_norm(args, j, i);
		j++;
	}
}

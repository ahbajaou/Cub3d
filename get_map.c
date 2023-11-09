/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: himejjad <himejjad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:10:43 by himejjad          #+#    #+#             */
/*   Updated: 2023/11/09 21:45:13 by himejjad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_coma(char *args)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (args[i])
	{
		if (args[i] == ',')
			count++;
		i++;
	}
	if (count != 2)
		error();
	return (count);
}

void	check_max_rgb(t_args *args)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	if (args->rgb == NULL)
		error();
	while (args->rgb[i])
	{
		j = 0;
		while (args->rgb[i][j])
		{
			if (!isdigit(args->rgb[i][j]))
				error();
			j++;
		}
		if (atoi(args->rgb[i]) > 255 || atoi(args->rgb[i]) < 0)
			error();
		i++;
	}
	if (i != 3)
		error();
}

void	check_espa(char *args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (args[i] == ' ')
			error();
		i++;
	}
}

void	get_rgb(t_args *args)
{
	check_espa(args->floor);
	check_espa(args->cell);
	check_coma(args->floor);
	check_coma(args->cell);
	check_espa(args->so);
	check_espa(args->we);
	check_espa(args->ea);
	check_espa(args->no);
	args->rgb = ft_split(args->floor, ',');
	check_max_rgb(args);
	args->floor_r = atoi(args->rgb[0]);
	args->floor_g = atoi(args->rgb[1]);
	args->floor_b = atoi(args->rgb[2]);
	args->rgb = NULL;
	args->rgb = ft_split(args->cell, ',');
	check_max_rgb(args);
	args->cell_r = atoi(args->rgb[0]);
	args->cell_g = atoi(args->rgb[1]);
	args->cell_b = atoi(args->rgb[2]);
}

t_args	*get_map(t_args *args)
{
	char	*stock;

	stock = get_next_line(args->fd);
	if (!stock)
		error();
	args->str = NULL;
	while (stock)
	{
		args->str = ft_strjoin(args->str, stock);
		free(stock);
		stock = get_next_line(args->fd);
	}
	args->argv = ft_split(args->str, '\n');
	args->copy = args->argv + 6;
	args->copy2 = args->copy;
	args->width = ft_strlen(args->copy[0]);
	check_face(args);
	check_n_w_s_e(args);
	get_deriction(args);
	args->height = count_lines(args->copy);
	skip_space(args);
	get_rgb(args);
	return (args);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: himejjad <himejjad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 07:53:04 by himejjad          #+#    #+#             */
/*   Updated: 2023/11/10 19:59:18 by himejjad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_wall(t_args *args, int j, int i)
{
	int	x;

	x = 0;
	while (args->copy[args->height - 1][x])
	{
		if (args->copy[args->height - 1][x] != '1')
		{
			if (args->copy[args->height - 1][x] == '0')
				error();
		}
		x++;
	}
	while (args->copy[i][j])
	{
		if (args->copy[i][j] != '1')
		{
			if (args->copy[i][j] == ' ')
				j++;
			else if (args->copy[i][j] == '0')
				error();
		}
		j++;
	}
}

void	check_wall2(t_args *args)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!args->copy[0])
		error();
	check_wall(args, j, i);
	i++;
	while (i < args->height)
	{
		args->width = ft_strlen(args->copy[i]);
		if (args->copy[i][0] != '1' || args->copy[i][args->width] != '1')
		{
			if (args->copy[i][0] == ' ' && args->copy[i][args->width
				- 1] == ' ')
				i++;
			if (args->copy[i][0] == '0' || args->copy[i][args->width
				- 1] == '0')
				error();
		}
		i++;
	}
}

char	*ft_strdup(const char *s1)
{
	char	*s11;
	char	*s22;
	int		i;
	int		x;

	s11 = (char *)s1;
	i = 0;
	x = 0;
	s22 = malloc(sizeof(char) * (ft_strlen(s11) + 1));
	if (!s22)
		return (NULL);
	while (s11[i])
	{
		s22[x] = s11[i];
		x++;
		i++;
	}
	s22[x] = '\0';
	return (s22);
}

int	check_cub(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (!file)
		error();
	if (file[len - 1] == 'b' && file[len - 2] == 'u' && file[len - 3] == 'c'
		&& file[len - 4] == '.')
		return (1);
	return (0);
}

void	check_xpm(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (!file)
		error();
	if (file[len - 1] != 'm' && file[len - 2] != 'p' && file[len - 3] != 'x'
		&& file[len - 4] != '.')
		error();
}

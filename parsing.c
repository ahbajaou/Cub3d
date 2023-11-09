/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: himejjad <himejjad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 07:53:04 by himejjad          #+#    #+#             */
/*   Updated: 2023/11/09 21:47:43 by himejjad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void	check_wall2(t_args *args)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	 if(!args->copy[0])
        error();
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

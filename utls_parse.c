/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utls_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: himejjad <himejjad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 08:00:19 by himejjad          #+#    #+#             */
/*   Updated: 2023/11/10 17:17:25 by himejjad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error(void)
{
	write(1, "\033[31m", 5);
	write(1, "ERROR\n", 6);
	exit(1);
}

size_t	count_word(const char *s, char c)
{
	size_t	i;
	size_t	x;

	i = 0;
	x = 0;
	while (s[i])
	{
		if ((s[i] != c && s[i + 1] == c) || (s[i + 1] == '\0' && s[i] != c))
			x++;
		i++;
	}
	return (x);
}

int	count_caracters(const char *s, char c, size_t pos)
{
	int	i;

	i = 0;
	while (s[pos] != c && s[pos] != '\0')
	{
		pos++;
		i++;
	}
	return (i);
}

char	**ft_split(char *s, char c)
{
	char	**new;
	size_t	co;
	size_t	i;
	size_t	pos;
	size_t	x;

	if (!s)
		return (NULL);
	i = 0;
	pos = 0;
	x = count_word(s, c);
	new = malloc(sizeof(char *) * (x + 1));
	if (!new)
		return (NULL);
	new[x] = NULL;
	while (i < x)
	{
		while (s[pos] == c)
			pos++;
		co = count_caracters(s, c, pos);
		new[i] = ft_substr(s, pos, co);
		pos += co;
		i++;
	}
	return (new);
}

int	count_lines(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

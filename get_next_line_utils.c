/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: himejjad <himejjad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 22:10:15 by himejjad          #+#    #+#             */
/*   Updated: 2023/03/06 22:06:30 by himejjad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char	*s1, char	*s2)
{
	char	*join;
	int		len;
	int		x;
	int		j;
	int		i;

	x = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	join = malloc(len + 1);
	if (!join)
		return (NULL);
	j = ft_strlen(s1);
	i = ft_strlen(s2);
	while (x < j)
	{
		join[x] = s1[x];
		x++;
	}
	len = 0;
	while (len < i)
		join[x++] = s2[len++];
	join[x] = '\0';
	free(s1);
	return (join);
}

char	*ft_substr(char *s1, int start, int len)
{
	int		i;
	int		x;
	char	*new;

	i = 0;
	x = 0;
	if (!s1)
		return (NULL);
	if (start >= ft_strlen(s1))
		len = 0;
	while (i < len && s1[start + i])
		i++;
	new = malloc(i + 1);
	if (!new)
		return (0);
	while (x < i)
	{
		new[x] = s1[start + x];
		x++;
	}
	new[x] = '\0';
	return (new);
}

char	*ft_line(char *buffer)
{
	int		i;
	char	*line;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = ft_substr(buffer, 0, i + 1);
	return (line);
}

char	*ft_next(char *buffer)
{
	int		i;
	char	*line;

	i = 0;
	if (!buffer)
		return (NULL);
	while (buffer[i])
	{
		if (buffer[i] == '\n')
		{
			line = ft_substr(buffer, i + 1, ft_strlen(buffer));
			free (buffer);
			return (line);
		}
		i++;
	}
	free (buffer);
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mini_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbajaou <ahbajaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:41:25 by ahbajaou          #+#    #+#             */
/*   Updated: 2023/11/10 11:48:31 by ahbajaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	drawplayer(t_ray *ray)
{
	float	i;
	float	j;

	i = -1;
	j = -1;
	while (i <= 1)
	{
		j = -1;
		while (j <= 1)
		{
			my_mlx_pixel_put(ray, ((ray->p->py / 64) * 5) + j,
				((ray->p->px / 64) * 5) + i, 0xff0000);
			j++;
		}
		i++;
	}
	return (0);
}

void	putpixel(t_ray *ray, int x, int y, int color)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			my_mlx_pixel_put(ray, y + j, x + i, color);
			j++;
		}
		i++;
	}
}

void	drawwall(t_ray *ray)
{
	int	p;
	int	k;

	p = 0;
	k = 0;
	while (p < ((ray->height / 64) * 5))
	{
		k = 0;
		while (k < ((ray->width / 64) * 5))
		{
			if (ray->map[p / 5][k / 5] == 0)
				break ;
			if (ray->map[p / 5][k / 5] == '1' || ray->map[p / 5][k / 5] == ' '
				|| ray->map[p / 5][k / 5] == '\0'
					|| ray->map[p / 5][k / 5] == '\n')
				putpixel(ray, p, k, 0xffffff);
			k += 5;
		}
		p += 5;
	}
}

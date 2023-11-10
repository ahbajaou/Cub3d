/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbajaou <ahbajaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 12:35:16 by ahbajaou          #+#    #+#             */
/*   Updated: 2023/11/10 12:40:41 by ahbajaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_ray *ray, int x, int y, int color)
{
	char	*dst;

	if (x <= 0 || x >= WIDTH || y <= 0 || y >= HEIGHT)
		return ;
	dst = ray->img->addr + (y * ray->img->line_length + x
			* (ray->img->bits_per_pixel / 8));
	*(int *)dst = color;
}

int	checkmaphawall(t_ray *ray, int x, int y, int size)
{
	int	x1;
	int	y1;

	if (x <= 0 || x >= ray->height || y <= 0 || y >= ray->width)
		return (1);
	x1 = (x / size);
	y1 = (y / size);
	if (ray->map[x1][y1] == '1' || ray->map[x1][y1] == ' '
		|| ray->map[x1][y1] == '\0' || ray->map[x1][y1] == '\n')
		return (1);
	return (0);
}

float	distamce2point(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

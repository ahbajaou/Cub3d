/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawrays.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbajaou <ahbajaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:35:44 by ahbajaou          #+#    #+#             */
/*   Updated: 2023/11/10 11:39:56 by ahbajaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_ray_with_distance(t_ray *ray, float x, float y, float angle)
{
	float	end_x;
	float	end_y;
	int		steps;
	int		i;

	i = 0;
	end_x = x + 10 * cos(angle);
	end_y = y + 10 * sin(angle);
	steps = 10;
	while (i < steps)
	{
		x += (end_x - x) / steps;
		y += (end_y - y) / steps;
		my_mlx_pixel_put(ray, y, x, 0xff0000);
		i++;
	}
}

void	drawray(t_ray *ray)
{
	int		num_rays;
	int		i;
	float	rayangle;

	i = 0;
	num_rays = 1;
	rayangle = ray->p->playerrotatangl;
	while (i < num_rays)
	{
		draw_ray_with_distance(ray, (ray->p->px / 64) * 5,
			(ray->p->py / 64) * 5, rayangle);
		rayangle += (float)1 / num_rays;
		i++;
	}
}

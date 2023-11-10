/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: himejjad <himejjad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:50:33 by ahbajaou          #+#    #+#             */
/*   Updated: 2023/11/10 16:28:25 by himejjad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	getofx(t_ray *ray)
{
	int	ofx;

	ofx = 0;
	if (ray->virti == 0)
	{
		ofx = fmod(ray->hit->wallhity, 64);
		if (ofx >= 63)
			ofx = fmod(ray->hit->wallhitx, 64);
	}
	else if (ray->virti == 1)
		ofx = fmod(ray->hit->wallhitx, 64) * 64 / 64;
	return (ofx);
}

void	findwallhit(t_ray *ray, float x, float y, float angle)
{
	int	x1;
	int	y1;
	int	i;

	i = 0;
	ray->virti = 0;
	while (1)
	{
		x1 = x + i * cos(angle);
		y1 = y + i * sin(angle);
		if (checkmaphawall(ray, x1, y1, 64) == 1)
			break ;
		i++;
	}
	ray->hit->wallhitx = x1;
	ray->hit->wallhity = y1;
	ray->hit->walldis = distamce2point(x1, y1, x, y);
	ray->hit->wallnewdis = ray->hit->walldis
		* cos(angle - ray->p->playerrotatangl);
	if (roundf(fmod(ray->hit->wallhitx, 64)) == 0)
		ray->virti = 0;
	else if (roundf(fmod(ray->hit->wallhity, 64)) == 0)
		ray->virti = 1;
	ray->hit->wallhei = (64 * HEIGHT) / ray->hit->wallnewdis;
}

void	draw3d_2(t_ray *ray, int i)
{
	int	h;
	int	ofy;

	h = 0;
	ray->hit->ofx = getofx(ray);
	while (h++ < (int)((HEIGHT - ray->hit->wallhei) / 2))
		my_mlx_pixel_put(ray, i, h,
			get_clr_rgb(ray->cell_r, ray->cell_g, ray->cell_b));
	while (h++ < (int)((HEIGHT - ray->hit->wallhei) / 2) + ray->hit->wallhei)
	{
		ofy = fmod(((h - (HEIGHT - ray->hit->wallhei) / 2)
					* 64) / ray->hit->wallhei, 64);
		my_mlx_pixel_put(ray, i, h, colors_img(ray, ray->hit->ofx, ofy));
	}
	while (h++ < HEIGHT)
		my_mlx_pixel_put(ray, i, h,
			get_clr_rgb(ray->floor_r, ray->floor_g, ray->floor_b));
}

void	draw3d(t_ray *ray)
{
	int	i;

	i = 0;
	ray->deriction = 0;
	ray->hit->angle_fov = -32;
	ray->hit->rayangle = ray->p->playerrotatangl - 32 * (PI / 180);
	while (i < WIDTH)
	{
		findwallhit(ray, ray->p->px + cos(ray->hit->rayangle
				+ (ray->hit->angle_fov * (PI / 180))),
			ray->p->py + sin(ray->hit->rayangle + (ray->hit->angle_fov
					* (PI / 180))), ray->hit->rayangle);
		draw3d_2(ray, i);
		ray->hit->rayangle += (float)1 / WIDTH;
		if (ray->hit->angle_fov <= 64)
			ray->hit->angle_fov += (float)1 / (WIDTH / 64);
		i++;
	}
}

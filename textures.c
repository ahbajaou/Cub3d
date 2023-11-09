/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: himejjad <himejjad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 21:55:27 by himejjad          #+#    #+#             */
/*   Updated: 2023/11/09 21:56:24 by himejjad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_image(t_ray *ray, int x, int y)
{
	ray->img = malloc(sizeof(t_ray) * 5);
	ray->img[1].img2 = mlx_xpm_file_to_image(ray->mlx, ray->no,
			&ray->img[1].texthei, &ray->img[1].textwid);
	ray->img[1].addr2 = mlx_get_data_addr(ray->img[1].img2,
			&ray->img[1].bits_per_pixel2, &ray->img[1].line_length2,
			&ray->img[1].endian2);
	ray->img[2].img2 = mlx_xpm_file_to_image(ray->mlx, ray->so,
			&ray->img[2].texthei, &ray->img[2].textwid);
	ray->img[2].addr2 = mlx_get_data_addr(ray->img[2].img2,
			&ray->img[2].bits_per_pixel2, &ray->img[2].line_length2,
			&ray->img[2].endian2);
	ray->img[3].img2 = mlx_xpm_file_to_image(ray->mlx, ray->we,
			&ray->img[3].texthei, &ray->img[3].textwid);
	ray->img[3].addr2 = mlx_get_data_addr(ray->img[3].img2,
			&ray->img[3].bits_per_pixel2, &ray->img[3].line_length2,
			&ray->img[3].endian2);
	ray->img[4].img2 = mlx_xpm_file_to_image(ray->mlx, ray->ea,
			&ray->img[4].texthei, &ray->img[4].textwid);
	ray->img[4].addr2 = mlx_get_data_addr(ray->img[4].img2,
			&ray->img[4].bits_per_pixel2, &ray->img[4].line_length2,
			&ray->img[4].endian2);
}

int	colors_img(t_ray *ray, int x, int y)
{
	finddirection(ray);
	if (x < 0 || y < 0)
		return (0);
	else if (ray->deriction == 1)
		ray->str = ray->img[1].addr2 + (y * ray->img[1].line_length2 + x
				* (ray->img[1].bits_per_pixel2 / 8));
	else if (ray->deriction == 2)
		ray->str = ray->img[2].addr2 + (y * ray->img[2].line_length2 + x
				* (ray->img[2].bits_per_pixel2 / 8));
	else if (ray->deriction == 3)
		ray->str = ray->img[3].addr2 + (y * ray->img[3].line_length2 + x
				* (ray->img[3].bits_per_pixel2 / 8));
	else if (ray->deriction == 4)
		ray->str = ray->img[4].addr2 + (y * ray->img[4].line_length2 + x
				* (ray->img[4].bits_per_pixel2 / 8));
	return (*(int *)ray->str);
}

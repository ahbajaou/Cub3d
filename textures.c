/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: himejjad <himejjad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 19:02:18 by himejjad          #+#    #+#             */
/*   Updated: 2023/11/10 19:39:12 by himejjad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_rgb(t_args *args)
{
	int	i;

	i = 0;
	while (args->rgb[i])
	{
		free(args->rgb[i]);
		i++;
	}
}

void	get_image_norm(t_ray *ray)
{
	ray->img->img3 = mlx_xpm_file_to_image(ray->mlx, ray->we,
			&ray->img->texthei, &ray->img->textwid);
	if (!ray->img->img3)
		error();
	ray->img->addr3 = mlx_get_data_addr(ray->img->img3,
			&ray->img->bits_per_pixel3, &ray->img->line_length3,
			&ray->img->endian3);
	ray->img->img4 = mlx_xpm_file_to_image(ray->mlx, ray->ea,
			&ray->img->texthei, &ray->img->textwid);
	if (!ray->img->img4)
		error();
	ray->img->addr4 = mlx_get_data_addr(ray->img->img4,
			&ray->img->bits_per_pixel4, &ray->img->line_length4,
			&ray->img->endian4);
}

void	get_image(t_ray *ray)
{
	ray->img->img1 = mlx_xpm_file_to_image(ray->mlx, ray->no,
			&ray->img->texthei, &ray->img->textwid);
	if (!ray->img->img1)
		error();
	ray->img->addr1 = mlx_get_data_addr(ray->img->img1,
			&ray->img->bits_per_pixel1, &ray->img->line_length1,
			&ray->img->endian1);
	ray->img->img2 = mlx_xpm_file_to_image(ray->mlx, ray->so,
			&ray->img->texthei, &ray->img->textwid);
	if (!ray->img->img2)
		error();
	ray->img->addr2 = mlx_get_data_addr(ray->img->img2,
			&ray->img->bits_per_pixel2, &ray->img->line_length2,
			&ray->img->endian2);
	get_image_norm(ray);
}

int	colors_img(t_ray *ray, int x, int y)
{
	finddirection(ray);
	if (x < 0 || y < 0)
		return (0);
	else if (ray->deriction == 1)
		ray->str = ray->img->addr1 + (y * ray->img->line_length1 + x
				* (ray->img->bits_per_pixel1 / 8));
	else if (ray->deriction == 2)
		ray->str = ray->img->addr2 + (y * ray->img->line_length2 + x
				* (ray->img->bits_per_pixel2 / 8));
	else if (ray->deriction == 3)
		ray->str = ray->img->addr3 + (y * ray->img->line_length3 + x
				* (ray->img->bits_per_pixel3 / 8));
	else if (ray->deriction == 4)
		ray->str = ray->img->addr4 + (y * ray->img->line_length4 + x
				* (ray->img->bits_per_pixel4 / 8));
	return (*(int *)ray->str);
}

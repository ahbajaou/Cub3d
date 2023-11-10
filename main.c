/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbajaou <ahbajaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 13:49:16 by ahbajaou          #+#    #+#             */
/*   Updated: 2023/11/10 14:05:22 by ahbajaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	draw(t_ray *ray)
{
	ray->img->img = mlx_new_image(ray->mlx, WIDTH, HEIGHT);
	ray->img->addr = mlx_get_data_addr(ray->img->img, &ray->img->bits_per_pixel,
			&ray->img->line_length, &ray->img->endian);
	update(ray);
	draw3d(ray);
	if (ray->flagmap == 1)
	{
		drawplayer(ray);
		drawwall(ray);
		drawray(ray);
	}
	mlx_put_image_to_window(ray->mlx, ray->mlx_win, ray->img->img, 0, 0);
	mlx_destroy_image(ray->mlx, ray->img->img);
	return (0);
}

void	raycasting(t_ray *ray)
{
	get_sizeofmap(ray);
	ray->mlx = mlx_init(ray);
	ray->mlx_win = mlx_new_window(ray->mlx, WIDTH, HEIGHT, "Cub3D");
	get_image(ray, WIDTH, HEIGHT);
	player_position(ray);
	mlx_hook(ray->mlx_win, 2, 0, keyupdate2, ray);
	mlx_hook(ray->mlx_win, 3, 0, keyupdate1, ray);
	mlx_loop_hook(ray->mlx, draw, ray);
	mlx_loop(ray->mlx);
}

int	main(int ac, char **av)
{
	t_args	*args;
	t_ray	*ray;

	ray = NULL;
	args = malloc(sizeof(t_args));
	args->fd = open (av[1], O_RDONLY);
	ray = malloc(sizeof(t_ray));
	ray->img = malloc(sizeof(t_img));
	ray->p = malloc(sizeof(t_player));
	ray->hit = malloc(sizeof(t_hitray));
	if (ac == 2 && check_cub(av[1]))
	{
		args = get_map(args);
		check_wall2(args);
		exchange(ray, args);
		ray->map = args->copy;
		raycasting(ray);
	}
	else
		error();
}

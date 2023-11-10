/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbajaou <ahbajaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 12:41:47 by ahbajaou          #+#    #+#             */
/*   Updated: 2023/11/10 12:44:04 by ahbajaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_clr_rgb(int r, int g, int b)
{
	return (r * 256 * 256 + g * 256 + b);
}

int	finddirection(t_ray *ray)
{
	if (ray->map[(int)((ray->hit->wallhitx - 1) / 64)]
			[(int)(ray->hit->wallhity / 64)] == '0')
		ray->deriction = 1;
	if (ray->map[(int)((ray->hit->wallhitx + 1) / 64)]
			[(int)(ray->hit->wallhity / 64)] == '0')
		ray->deriction = 2;
	if (ray->map[(int)(ray->hit->wallhitx / 64)]
			[(int)((ray->hit->wallhity - 1) / 64)] == '0')
		ray->deriction = 3;
	if (ray->map[(int)(ray->hit->wallhitx / 64)]
			[(int)((ray->hit->wallhity + 1) / 64)] == '0')
		ray->deriction = 4;
	return (ray->deriction);
}

void	exchange(t_ray *ray, t_args *args)
{
	ray->ea = args->ea;
	ray->we = args->we;
	ray->no = args->no;
	ray->so = args->so;
	ray->cell_b = args->cell_b;
	ray->cell_r = args->cell_r;
	ray->cell_g = args->cell_g;
	ray->floor_b = args->floor_b;
	ray->floor_r = args->floor_r;
	ray->floor_g = args->floor_g;
}

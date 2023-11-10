/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: himejjad <himejjad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 12:13:26 by ahbajaou          #+#    #+#             */
/*   Updated: 2023/11/10 16:38:04 by himejjad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	moves_calcul(t_ray *ray)
{
	float	angel;

	if (ray->p->playerwalkdirec != 0)
	{
		if (ray->flag)
		{
			angel = ray->p->playerrotatangl - M_PI_2;
			ray->p->playerx *= cos(angel);
			ray->p->playery *= sin(angel);
		}
		else
		{
			ray->p->playerx *= cos(ray->p->playerrotatangl);
			ray->p->playery *= sin(ray->p->playerrotatangl);
		}
		ray->p->playerx += ray->p->px;
		ray->p->playery += ray->p->py;
	}
}

int	update(t_ray *ray)
{
	ray->p->playerrotatangl += ray->p->playertunrdirec
		* ray->p->turnspeed;
	ray->p->movestep = ray->p->playerwalkdirec * ray->p->walkspeed;
	ray->p->playerx = ray->p->movestep;
	ray->p->playery = ray->p->movestep;
	moves_calcul(ray);
	if (checkmaphawall(ray, ray->p->playerx, ray->p->playery, 64) == 0)
	{
		if (ray->map[(int)(ray->p->playerx / 64
				+ (cos(ray->p->playerrotatangl)))]
					[(int)(ray->p->playery / 64)] != '1')
			ray->p->px = ray->p->playerx;
		if (ray->map[(int)(ray->p->playerx / 64)]
			[(int)(ray->p->playery / 64
				+ (sin(ray->p->playerrotatangl)))] != '1')
			ray->p->py = ray->p->playery;
	}
	return (0);
}

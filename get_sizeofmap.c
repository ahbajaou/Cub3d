/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sizeofmap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbajaou <ahbajaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:19:43 by ahbajaou          #+#    #+#             */
/*   Updated: 2023/11/10 11:23:00 by ahbajaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_sizeofmap(t_ray *ray)
{
	int	p;
	int	px;
	int	maxwid;

	p = 0;
	px = 0;
	maxwid = 0;
	while (ray->map[p])
	{
		px = ft_strlen(ray->map[p]);
		if (px > maxwid)
			maxwid = px;
		p++;
	}
	ray->height = p * 64;
	ray->width = maxwid * 64;
}

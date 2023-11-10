/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_position.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahbajaou <ahbajaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:26:43 by ahbajaou          #+#    #+#             */
/*   Updated: 2023/11/10 11:31:31 by ahbajaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_rot(char c, t_ray *ray, int i, int j)
{
	if (c == 'N')
		ray->p->playerrotatangl = 360;
	else if (c == 'S')
		ray->p->playerrotatangl = 180;
	else if (c == 'E')
		ray->p->playerrotatangl = 60;
	else if (c == 'W')
		ray->p->playerrotatangl = 270;
	ray->map[i][j] = '0';
	ray->p->px = i * 64;
	ray->p->py = j * 64;
	ray->p->playertunrdirec = 0;
	ray->p->playerwalkdirec = 0;
	ray->p->walkspeed = 17;
	ray->p->turnspeed = 17 * (PI / 180);
	ray->flag = 0;
}

void	player_position(t_ray *ray)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (ray->map[i])
	{
		j = 0;
		while (ray->map[i][j])
		{
			if (ray->map[i][j] == 'N' || ray->map[i][j] == 'S'
				|| ray->map[i][j] == 'E' || ray->map[i][j] == 'W')
			{
				get_rot(ray->map[i][j], ray, i, j);
				break ;
			}
			j++;
		}
		i++;
	}
}

void	draw_wall(t_map *m)
{
	if (m->dda->direction == 1 || m->dda->direction == 2)
		m->dda->flag = fmod(m->dda->y / 64, 1);
	else if (m->dda->direction == 3 || m->dda->direction == 4)
		m->dda->flag = fmod(m->dda->x / 64, 1);
	m->dda->flag *= 64;
	if (check_wall(m, m->dda->x, m->dda->y))
		my_mlx_pixel_put(m, m->dda->w, m->dda->h, \
		get_color_image(m, m->dda->flag, \
		(((m->dda->h - ((m->height - m->dda->wall) / 2)) * 64) \
		/ m->dda->wall), m->dda->direction));
}

void	final_draw(t_map *m)
{
	m->dda->direction = check_direction_of_texture(m, m->dda->x, m->dda->y);
	m->dda->h = 0;
	while (m->dda->h < m->height && m->dda->w < m->weight)
	{
		if (m->dda->h < (int)((m->height - m->dda->wall) / 2))
			my_mlx_pixel_put(m, m->dda->w, m->dda->h, \
			color_rgb(m->c_r, m->c_g, m->c_b));
		else if (m->dda->h < \
			(int)(((m->height - m->dda->wall) / 2) + m->dda->wall))
		{
			draw_wall(m);
		}
		else
			my_mlx_pixel_put(m, m->dda->w, m->dda->h, \
			color_rgb(m->f_r, m->f_g, m->f_b));
		m->dda->h++;
	}
}

void	calcul_wall(t_map *m)
{
	while (1)
	{
		if (check_wall(m, m->dda->x, m->dda->y))
			break ;
		m->dda->x += m->dda->xinc;
		m->dda->y += m->dda->yinc;
	}
	m->dda->dis = sqrt(pow(m->dda->x - m->player->p_x, 2) + \
		pow(m->dda->y - m->player->p_y, 2));
	m->dda->new_dis = m->dda->dis * cos(m->dda->angle_fov * (M_PI / 180));
	m->dda->wall = (64 * m->height) / m->dda->new_dis;
}

void	dda_line(int x1, int y1, t_map *m)
{
	m->dda->dx = x1 - m->player->p_x;
	m->dda->dy = y1 - m->player->p_y;
	if (abs(m->dda->dy) > abs(m->dda->dx))
		m->dda->steps = abs(m->dda->dy);
	else
		m->dda->steps = abs(m->dda->dx);
	m->dda->xinc = m->dda->dx / (float) m->dda->steps;
	m->dda->yinc = m->dda->dy / (float) m->dda->steps;
	m->dda->x = m->player->p_x;
	m->dda->y = m->player->p_y;
	calcul_wall(m);
	final_draw(m);
}

void	draw_3d(t_map *m)
{
	m->dda->angle_fov = -32;
	m->dda->angle = m->player->rot;
	m->dda->w = 0;
	while (m->dda->w < m->weight)
	{
		dda_line(m->player->p_x \
			+ sin(((m->dda->angle + m->dda->angle_fov) * \
			(M_PI / 180))) * 1000, \
			m->player->p_y + \
			cos(((m->dda->angle + m->dda->angle_fov) * \
			(M_PI / 180))) * 1000, m);
		if (m->dda->angle_fov <= 32)
			m->dda->angle_fov += (float)1 / (m->weight / 64);
		m->dda->w++;
	}
}

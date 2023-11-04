
#include "cub3d.h"


void	my_mlx_pixel_put(t_ray *ray, int x, int y, int color)
{
	char	*dst;
    // if (x <= 0 || x >= ray->width || y <= 0 || y >= ray->height)
    //         return ;
	dst = ray->img->addr + (y * ray->img->line_length + x * (ray->img->bits_per_pixel / 8));
	*( int*)dst = color;
}

int checkmaphawall(t_ray *ray, int x, int y,int size)
{
    if (x <= 0 || x >= ray->height || y <= 0 || y >= ray->width)
        return 1;
    int x1 = (x / size);
    int y1 = (y / size);
    if (ray->map[x1][y1] == '1' || ray->map[x1][y1] == ' ' || ray->map[x1][y1] == '\0' || ray->map[x1][y1] == '\n' )
        return 1;
    return 0;
    
}


float /*  */distamce2point(float x1,float y1,float x2,float y2)
{
    return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

int	keyupdate2(int keycode, t_ray *ray)
{
	if (keycode == 65307)
		exit(0);
	else if (keycode == DOWN)
		ray->p->playerwalkdirec = -1;
	else if (keycode == UP)
		ray->p->playerwalkdirec = 1;
	else if (keycode == RIGHT)
		ray->p->playertunrdirec = 1;
	else if (keycode == LEFT)
		ray->p->playertunrdirec = -1;
	else if (keycode == RIGHT_A)
	{
		ray->flag = 1;
		ray->p->playerwalkdirec = -1;
	}
	else if (keycode == LEFT_D)
	{
		ray->flag = 1;
		ray->p->playerwalkdirec = 1;
	}
    else if (keycode == 109)
        ray->flagmap = 1;
    else
	    return (0);
    return 0;
}

int	keyupdate1(int keycode, t_ray *ray)
{
	if (keycode == DOWN)
		ray->p->playerwalkdirec = 0;
	else if (keycode == UP)
		ray->p->playerwalkdirec = 0;
	else if (keycode == RIGHT)
		ray->p->playertunrdirec = 0;
	else if (keycode == LEFT)
		ray->p->playertunrdirec = 0;
	else if (keycode == RIGHT_A || keycode == LEFT_D)
	{
		ray->p->playerwalkdirec = 0;
		ray->flag = 0;
	}
    else if (keycode == 109)
        ray->flagmap = 0;
    else
        return 0;
    return 0;
}


int update(t_ray *ray)
{
    float playerx;
    float playery;
    float angel;
    ray->p->playerrotatangl += ray->p->playertunrdirec * ray->p->turnspeed * 0.5;
    float movestep = ray->p->playerwalkdirec * ray->p->walkspeed * 0.5;
        playerx = movestep;
        playery = movestep;
    if (ray->p->playerwalkdirec != 0)
    {
        if (ray->flag)
        {
            angel = ray->p->playerrotatangl - M_PI_2;
            playerx *= cos(angel);
            playery *= sin(angel);
        }
        else
        {
            playerx *= cos(ray->p->playerrotatangl);
            playery *= sin(ray->p->playerrotatangl);
        }
    }
    playerx += ray->p->px;
    playery += ray->p->py;
        if (ray->map[(int)playerx / 50][(int)playery / 50] != '1')
        {
            ray->p->px = playerx;
            ray->p->py = playery;
        }
    return 0;
}


int    drawplayer(t_ray *ray)
{
    float i = -1;
    float j = -1;
    while (i <= 2)
    {
        j = -1;
        while (j <= 2)
        {
            my_mlx_pixel_put(ray,((ray->p->py / 50) * 10) + j,((ray->p->px / 50) * 10) + i, 0xff0000);
            j++;
        }
        i++;
    }
    return (0);
}
void putpixel(t_ray *ray,int x,int y,int color)
{
    int i = 0;
    int j = 0;
    while (i < 9)
    {
        j = 0;
        while (j < 9)
        {
            my_mlx_pixel_put(ray,y + j,x + i,color);
            j++;
        }
        i++;
    }
}
void    drawwall(t_ray *ray)
{

    int p = 0;
    int k = 0;
    int j = (ray->height / 50) * 10;
    int i = (ray->width / 50) * 10;
    while (p < j)
    {
        k = 0;
        while (k < i)
        {
            if (ray->map[p / 10][k / 10] == 0)
                 break ;
            if (ray->map[p / 10][k / 10] == '1' || ray->map[p / 10][k / 10] == ' ' || ray->map[p / 10][k / 10] == '\0' || ray->map[p / 10][k / 10] == '\n')
                putpixel(ray,p,k,0xffffff);
            k += 10;
        } 
        p += 10;
    }
}
void    findwallhit(t_ray *ray,float x,float y,float angel)
{
    int x1;
    int y1;
    int i = 0;

    while (1)
    {
        x1 = x +  (i * cos(angel + ( PI / 180.0)));
        y1 = y +  (i * sin(angel + ( PI / 180.0)));
        if (checkmaphawall(ray,x1,y1,50) == 1)
            break;
        i++;
    }
    ray->hit->wallhitx = x1;
    ray->hit->wallhity = y1;
    ray->hit->walldis = distamce2point(x1,y1,x,y);
    ray->hit->wallnewdis = ray->hit->walldis * cos(angel - ray->p->playerrotatangl);
    ray->hit->wallhei = (50 * HEIGHT) / ray->hit->wallnewdis;
}

int	get_clr_rgb(int r, int g, int b)
{
	return (r * 256 * 256 + g * 256 + b);
}

// int	get_color_image(t_map *m, int x, int y, int direction)
// {
// 	char	*dst;

// 	if (direction == 1)
// 		dst = m->image[0].addr + (y * m->image[0].line_length + x 
// 			* (m->image[0].bits_per_pixel / 8));
// 	if (direction == 2)
// 		dst = m->image[1].addr + (y * m->image[1].line_length + x
// 			* (m->image[1].bits_per_pixel / 8));
// 	if (direction == 3)
// 		dst = m->image[2].addr + (y * m->image[2].line_length + x
// 			* (m->image[2].bits_per_pixel / 8));
// 	if (direction == 4)
// 		dst = m->image[3].addr + (y * m->image[3].line_length + x 
// 			* (m->image[3].bits_per_pixel / 8));
// 	return (*(int *)dst);
// }
// void	draw_wall(t_map *m)
// {
// 	if (m->dda->direction == 1 || m->dda->direction == 2)
// 		m->dda->flag = fmod(m->dda->y / 64, 1);
// 	else if (m->dda->direction == 3 || m->dda->direction == 4)
// 		m->dda->flag = fmod(m->dda->x / 64, 1);
// 	m->dda->flag *= 64;
// 	if (check_wall(m, m->dda->x, m->dda->y))
// }

void draw_line(t_ray *ray)
{
    int i = 0;
    int h = 0;
      ray->deriction = 0;
    ray->hit->angle_fov = -32;
    ray->hit->rayangle = ray->p->playerrotatangl - 32 * (PI / 180);
    while (i <= WIDTH)
    {
        h = 0;
        findwallhit(ray,ray->p->px + cos(ray->hit->rayangle + (ray->hit->angle_fov * (PI / 180))),
            ray->p->py + sin(ray->hit->rayangle + (ray->hit->angle_fov * (PI / 180))) ,ray->hit->rayangle);
        //take the wallhitx and wallhity here for your texture
        while (h < HEIGHT && i < WIDTH)
        {
            if (h <= (HEIGHT - ray->hit->wallhei) / 2)
            {
                    my_mlx_pixel_put(ray,i,h,get_clr_rgb(ray->cell_r, ray->cell_g, ray->cell_b));
                    // printf("----i == %d---h == %d-------\n",i,h);
                    // printf("-----%f-----\n",(HEIGHT - ray->hit->wallhei) / 2);
            }
// 		my_mlx_pixel_put(m, m->dda->w, m->dda->h,get_color_image(m, m->dda->flag, (((m->dda->h - ((m->height - m->dda->wall) / 2)) * 64) / m->dda->wall), m->dda->direction));
                //you can make you texture here for the floor
            else if (h < ((HEIGHT - ray->hit->wallhei) / 2) + ray->hit->wallhei)
            {
                if (checkmaphawall(ray,ray->hit->wallhitx,ray->hit->wallhity,50) ==1)
                {

                        // my_mlx_pixel_put(ray,i,h,0xFFB833);
                        // printf("----[%f]--\n", (((h - ((HEIGHT - ray->hit->wallhei) / 2 ))) / ray->hit->wallhei));
                        // ray->deriction = 1;
                        //  my_mlx_pixel_put(ray,i,h,colors_img(ray, i,h));
                    //  my_mlx_pixel_put(ray,i,h,colors_img(ray, flag,(h - ((HEIGHT - (int)ray->hit->wallhei) / 2)) * 50) / (int)ray->hit->wallhei);
                    // (((m->dda->h - ((HEIGHT - ray->hit->wallhei) / 2 )) *50) / ray->hit->wallhei)
                    double flag1 = fmod(ray->hit->wallhitx / 50,1);
                    double flag = fmod(ray->hit->wallhity / 50,1);
                    flag *= 50;
                    flag1 *= 50;

                    //  my_mlx_pixel_put(ray,i,h,colors_img(ray, flag,(h - ((HEIGHT - ray->hit->wallhei) / 2 ))) / ray->hit->wallhei);
                     my_mlx_pixel_put(ray,i,h,colors_img(ray,(int) flag1,(int)flag));
                }
                    // if (checkmaphawall(ray,ray->hit->wallhitx,ray->hit->wallhity + 1,50) == 1)
                    //   my_mlx_pixel_put(ray,i,h,0xFFB833);
                    // if (checkmaphawall(ray,ray->hit->wallhitx + 1,ray->hit->wallhity + 1,50) == 1)
                    //     my_mlx_pixel_put(ray,i,h,0x8EF21D);
                        // you can make you texture here for the wall
            }
            else
                my_mlx_pixel_put(ray,i,h,get_clr_rgb(ray->floor_r, ray->floor_g, ray->floor_b));
                // you can make you texture here for the sky

            h++;
        }
        ray->hit->rayangle += (float)1 / WIDTH;
        if (ray->hit->angle_fov <= 32)
            ray->hit->angle_fov += (float)1 / (WIDTH / 50);
        i++;
    }
}


void draw_ray_with_distance(t_ray *ray, float x, float y, float angle)
{
    float end_x = x + 10 * cos(angle);
    float end_y = y + 10 * sin(angle);

    int steps = 10;  

    for (int i = 0; i < steps; i++)
    {
        x += (end_x - x) / steps;
        y += (end_y - y) / steps;
        my_mlx_pixel_put(ray, (y), (x), 0xff0000);
    }
}

void     drawray(t_ray *ray)
{
    int num_rays = 1;
    float rayangle = ray->p->playerrotatangl;
    int i = 0;
    while (i < num_rays)
    {

        // wallraycast(ray,(ray->p->px / 50) * 10,(ray->p->py / 50) * 10,rayangle);
        // draw_line_with_angle(ray,(ray->p->py / 50) * 10,(ray->p->px / 50) * 10,(ray->hit->wallhity),ray->hit->wallhitx);
        draw_ray_with_distance(ray,(ray->p->px / 50) * 10,(ray->p->py / 50) * 10,rayangle);
        rayangle += (float)1 / num_rays;
        i++;
    }
}
int    draw(t_ray *ray)
{
    // int i = 0;
    // int j = 0;
    ray->img->img = mlx_new_image(ray->mlx,WIDTH,HEIGHT);
	ray->img->addr = mlx_get_data_addr(ray->img->img, &ray->img->bits_per_pixel, &ray->img->line_length,&ray->img->endian);
    update(ray);
    draw_line(ray);
    if (ray->flagmap == 1)
    {
        drawplayer(ray);
        drawwall(ray);
        // exit(0);
        drawray(ray);
    }
    // draw3d(ray);
     	// mlx_put_image_to_window(ray->mlx, ray->mlx_win, ray->img->img2, 0,0);
    mlx_put_image_to_window(ray->mlx, ray->mlx_win, ray->img->img, 0, 0);
    mlx_destroy_image(ray->mlx,ray->img->img);
    return (0);
}

void get_rot(char c,t_ray *ray)
{
    if (c == 'N')
		ray->p->playerrotatangl = 270;
    else if (c == 'S')
		ray->p->playerrotatangl = 90;
    else if (c == 'E')
		ray->p->playerrotatangl = 0;
    else if (c == 'W')
		ray->p->playerrotatangl = 80;

}

void    player_position(t_ray *ray)
{
    int i = 0;
    int j = 0;
    while (ray->map[i])
    {
        j = 0;
        while (ray->map[i][j])
        {
            if (ray->map[i][j] == 'N' || ray->map[i][j] == 'S' || ray->map[i][j] == 'E' || ray->map[i][j] == 'W')
            {
                get_rot(ray->map[i][j],ray);
                ray->map[i][j] = '0';
                ray->p->px = i * 50;
                ray->p->py = j * 50;
                ray->p->playertunrdirec = 0;
                ray->p->playerwalkdirec = 0;
                ray->p->walkspeed = 4;
                ray->p->turnspeed = 4 * (PI / 180);
                ray->flag = 0;
                break;
            }
            j++;
        }
        i++;
    }

}

void exchange(t_ray *ray, t_args *args)
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

int    mouse(void)
{
    exit(0);
    return 0;
}
int main(int ac, char **av)
{
    t_args *args;

    args = malloc(sizeof(t_args));
    // int y = 0;
    // int x = 0;
    args->fd = open (av[1], O_RDONLY);
    t_ray *ray = NULL;
    ray  = malloc(sizeof(t_ray));
    ray->img = malloc(sizeof(t_img));
    ray->p = malloc(sizeof(t_player));
    ray->hit = malloc(sizeof(t_hitray));
    if (ac == 2 && check_cub(av[1]))
    {
        args = get_map(args);
        check_wall2(args);
        exchange(ray, args);
        ray->map = args->copy;
        int i = 0;
        while (ray->map[i])
            i++;
        ray->height = i * 50;
        int p = 0;
        int px = 0;
        int maxLength = 0;
        ray->width = 0;
        while (ray->map[p])
        {
            px = ft_strlen(ray->map[p]);
            if (px > maxLength)
                maxLength = px;
            p++;
        }
        ray->width = maxLength * 50;;
	    ray->mlx = mlx_init(ray);
	    ray->mlx_win = mlx_new_window(ray->mlx,WIDTH,HEIGHT,"Cub3D");
        get_image(ray,WIDTH,HEIGHT);
        player_position(ray);
      
        mlx_hook(ray->mlx_win,2,1L,keyupdate2,ray);
        mlx_hook(ray->mlx_win,3,2L,keyupdate1,ray);
        mlx_hook(ray->mlx_win,17,0,mouse,ray);
        mlx_loop_hook(ray->mlx,draw,ray);
	    mlx_loop(ray->mlx);
    }
    else 
        error();
}

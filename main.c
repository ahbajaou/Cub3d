
#include "cub3d.h"


void	my_mlx_pixel_put(t_ray *ray, int x, int y, int color)
{
	char	*dst;
    if (x <= 0 || x >= WIDTH || y <= 0 || y >= HEIGHT)
            return ;
	dst = ray->img->addr + (y * ray->img->line_length + x * (ray->img->bits_per_pixel / 8));
	*( int*)dst = color;
}

int checkmaphawall(t_ray *ray, int x, int y,int size)
{
    if (x <= 0 || x >= ray->height || y <= 0 || y >= ray->width)
        return 1;
    //   if (x <= 0 || x >= HEIGHT || y <= 0 || y >= WIDTH)
    //     return 1;
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


// int update(t_ray *ray)
// {
//     float playerx;
//     float playery;
//     float angel;
//     ray->p->playerrotatangl += ray->p->playertunrdirec * ray->p->turnspeed * 0.5;
//     float movestep = ray->p->playerwalkdirec * ray->p->walkspeed * 0.5;
//     playerx = movestep;
//     playery = movestep;
//     if (ray->p->playerwalkdirec != 0)
//     {
//         if (ray->flag)
//         {
//             angel = ray->p->playerrotatangl - M_PI_2;
//             playerx *= cos(angel);
//             playery *= sin(angel);
//         }
//         else
//         {
//             playerx *= cos(ray->p->playerrotatangl);
//             playery *= sin(ray->p->playerrotatangl);
//         }
//     }
//     playerx += ray->p->px;
//     playery += ray->p->py;
//     // int wallx = (playerx / 32) + cos(ray->p->playerrotatangl);
//     // int wally = (playery / 32) + sin(ray->p->playerrotatangl);
//     if (ray->map[(int)((playerx / 32) + cos(ray->p->playerrotatangl))][(int)((playery / 32) + sin(ray->p->playerrotatangl))] != '1')
//     {
//         ray->p->px = playerx;
//         ray->p->py = playery;
//     }
//     else 
//     {
//         // Handle sliding
//         if (ray->map[tile_x][(int)(ray->p->py / 32)] != '1') 
//         {
//             // Slide along the X-axis
//             ray->p->px = new_x;
//         } else if (ray->map[(int)(ray->p->px / 32)][tile_y] != '1') 
//         {
//             // Slide along the Y-axis
//             ray->p->py = new_y;
//         }
//     }
//     return (0);
// }
int update(t_ray *ray) {
    float playerx;
    float playery;
    float angel;
    ray->p->playerrotatangl += ray->p->playertunrdirec * ray->p->turnspeed * 0.5;
    float movestep = ray->p->playerwalkdirec * ray->p->walkspeed * 0.5;
    playerx = movestep;
    playery = movestep;

    if (ray->p->playerwalkdirec != 0) {
        if (ray->flag) {
            angel = ray->p->playerrotatangl - M_PI_2;
            playerx *= cos(angel);
            playery *= sin(angel);
        } else {
            playerx *= cos(ray->p->playerrotatangl);
            playery *= sin(ray->p->playerrotatangl);
        }
    }

    float new_x = ray->p->px + playerx;
    float new_y = ray->p->py + playery;

    int tile_x = (new_x / 32) + cos(ray->p->playerrotatangl);
    int tile_y = (new_y / 32) + sin(ray->p->playerrotatangl);

    // Check if the next position is a wall ('1')
    if (ray->map[tile_x][tile_y] != '1') {
        ray->p->px = new_x;
        ray->p->py = new_y;
    } else {
        // Handle sliding
        if (ray->map[tile_x][(int)((ray->p->py / 32) + sin(ray->p->playerrotatangl))] != '1') {
            // Slide along the X-axis
            ray->p->px = new_x;
        } else if (ray->map[(int)((ray->p->px / 32) + cos(ray->p->playerrotatangl))][tile_y] != '1') {
            // Slide along the Y-axis
            ray->p->py = new_y;
        }
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
            my_mlx_pixel_put(ray,((ray->p->py / 32) * 5) + j,((ray->p->px / 32) * 5) + i, 0xff0000);
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
    while (i < 4)
    {
        j = 0;
        while (j < 4)
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
    int j = (ray->height / 32) * 5;
    int i = (ray->width / 32) * 5;
    while (p < j)
    {
        k = 0;
        while (k < i)
        {
            if (ray->map[p / 5][k / 5] == 0)
                 break ;
            if (ray->map[p / 5][k / 5] == '1' || ray->map[p / 5][k / 5] == ' ' || ray->map[p / 5][k / 5] == '\0' || ray->map[p / 5][k / 5] == '\n')
                putpixel(ray,p,k,0xffffff);
            k += 5;
        } 
        p += 5;
    }
}

int	get_clr_rgb(int r, int g, int b)
{
	return (r * 256 * 256 + g * 256 + b);
}

void findwallhit(t_ray *ray, float x, float y, float angle)
{
    int x1;
    int y1;
    int i = 0;


    while (1)
    {
        x1 = x + i * cos(angle + (PI / 180.0));
        y1 = y + i * sin(angle + (PI / 180.0));
        
        if (checkmaphawall(ray, x1, y1, 32) == 1)
            break;
        
        i++;
    }

    ray->hit->wallhitx = x1;
    ray->hit->wallhity = y1;
   ray->hit->walldis = distamce2point(x1,y1,x,y);
    ray->hit->wallnewdis = ray->hit->walldis * cos(angle - ray->p->playerrotatangl);

    // Calculate the wall slope
    ray->virti = 0;

    if (roundf(fmod(ray->hit->wallhitx,32)) == 0)
    {
        // printf("-----0000----\n");
        // ray->horizo = 0;
        ray->virti = 0;

    }
    else if (roundf(fmod(ray->hit->wallhity,32)) == 0)
    {
        ray->virti = 1;
        // printf("---------\n");
        // ray->horizo = 1;
    }
    ray->hit->wallhei = (32 * HEIGHT) / ray->hit->wallnewdis;
    int heightwall = (int)ray->hit->wallhei;
    ray->hit->wallhittop = (HEIGHT - heightwall) / 2;
    
    if (ray->hit->wallhittop < 0)
        ray->hit->wallhittop = 0;
    // (int)(((m->height - m->dda->wall) / 2) + m->dda->wall))
    ray->hit->wallhitboton = (HEIGHT - heightwall) + heightwall;
    if (ray->hit->wallhitboton > HEIGHT)
        ray->hit->wallhitboton = HEIGHT;
}

int finddirection(t_ray *ray)
{
    // int direction;
    // printf("=-=-=-=-=->%f\n", ray->p->px);
	if (ray->map[(int)((ray->hit->wallhitx - 1) / 32)][(int)(ray->hit->wallhity / 32)] == '0')
		ray->deriction = 1;
	if (ray->map[(int)((ray->hit->wallhitx + 1) / 32)][(int)(ray->hit->wallhity / 32)] == '0')
		ray->deriction = 2;
	 if (ray->map[(int)(ray->hit->wallhitx / 32)][(int)((ray->hit->wallhity - 1) / 32)] == '0')
		ray->deriction = 3;
	if (ray->map[(int)(ray->hit->wallhitx / 32)][(int)((ray->hit->wallhity + 1) / 32)] == '0')
		ray->deriction = 4;
    return (ray->deriction);
}

void draw_line(t_ray *ray)
{
    int i = 0;
    int h = 0;
      ray->deriction = 0;
    ray->hit->angle_fov = -32;
    ray->hit->rayangle = ray->p->playerrotatangl - 32 * (PI / 180);
    int ofy;
    ray->hit->direction = finddirection(ray);
    while (i < WIDTH)
    {

        findwallhit(ray,ray->p->px + cos(ray->hit->rayangle + (ray->hit->angle_fov * (PI / 180))),
            ray->p->py + sin(ray->hit->rayangle + (ray->hit->angle_fov * (PI / 180))) ,ray->hit->rayangle);
        h = 0;
        int ofx = 0;
                if (ray->virti == 0)
                {
                    ofx = fmod(ray->hit->wallhity,32);
                    // printf("-----%d----------\n",ofx);
                    if (ofx >= 63)
                        ofx = fmod(ray->hit->wallhitx,32);
                    // printf("-----%d----------\n",ofx);

                }
                else if (ray->virti == 1)
                {
                    ofx = fmod(ray->hit->wallhitx,32) * 32 / 32;
                }
        while (h < (int)((HEIGHT - ray->hit->wallhei) / 2))
        {
                my_mlx_pixel_put(ray,i,h,get_clr_rgb(ray->cell_r, ray->cell_g, ray->cell_b));
                h++;
        }
        while (h < (int)((HEIGHT - ray->hit->wallhei) / 2 ) + ray->hit->wallhei)
        {
            // ofy = ((h - (HEIGHT - ray->hit->wallhei) / 2) * 32) / ray->hit->wallhei;
            ofy = fmod(((h - (HEIGHT - ray->hit->wallhei) / 2) * 32) / ray->hit->wallhei, 32);
                my_mlx_pixel_put(ray,i,h,colors_img(ray,ofx,ofy));
            h++;
        }
        while (h < HEIGHT)
        {

            my_mlx_pixel_put(ray,i,h,get_clr_rgb(ray->floor_r, ray->floor_g, ray->floor_b));
            h++;
        }
        // }

        ray->hit->rayangle += (float)1 / WIDTH;
        if (ray->hit->angle_fov <= 32)
            ray->hit->angle_fov += (float)1 / (WIDTH / 32);
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
    int i = 0;
    float rayangle = ray->p->playerrotatangl;  //- 32 * (PI / 180);
    while (i < num_rays)
    {
        draw_ray_with_distance(ray,(ray->p->px / 32) * 5,(ray->p->py / 32) * 5,rayangle);
        rayangle += (float)1 / num_rays;
        i++;
    }
}

int    draw(t_ray *ray)
{

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
                ray->p->px = i * 32;
                ray->p->py = j * 32;
                ray->p->playertunrdirec = 0;
                ray->p->playerwalkdirec = 0;
                ray->p->walkspeed = 4;
                ray->p->turnspeed = 3 * (PI / 180);
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
    return (0);
}
int mouse_hook(int key)
{
    printf("--%d--\n",key);
    return key;
}
int main(int ac, char **av)
{
    t_args *args;

    args = malloc(sizeof(t_args));
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
        ray->height = i * 32;
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
        ray->width = maxLength * 32;
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
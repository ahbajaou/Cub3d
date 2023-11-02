
#include "cub3d.h"


void	my_mlx_pixel_put(t_ray *ray, int x, int y, int color)
{
	char	*dst;
    if (x <= 0 || x >= ray->width || y <= 0 || y >= ray->height)
            return ;
	dst = ray->img->addr + (y * ray->img->line_length + x * (ray->img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
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


float distamce2point(float x1,float y1,float x2,float y2)
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
    // exit(0);
    (void)color;
    (void)ray;
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
            // printf("--[%d]--\n",ray->map[p / 10][k / 10]);
            if (ray->map[p / 10][k / 10] == '1' || ray->map[p / 10][k / 10] == ' ' || ray->map[p / 10][k / 10] == '\0' || ray->map[p / 10][k / 10] == '\n')
            {
                putpixel(ray,p,k,0xffffff);
            }
            // j++;
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

void draw_line(t_ray *ray)
{
    int i = 0;
    int h = 0;
    ray->hit->angle_fov = -32;
    ray->hit->rayangle = ray->p->playerrotatangl - 32 * (PI / 180);
        // ray->p->playerrotatangl += FOV_ANGLE / WIDTH;
    while (i <= WIDTH)
    {
        // draw3d(ray);
        findwallhit(ray,ray->p->px + cos(ray->hit->rayangle + (ray->hit->angle_fov * (PI / 180))),
            ray->p->py + sin(ray->hit->rayangle + (ray->hit->angle_fov * (PI / 180))) ,ray->hit->rayangle);
        //take the wallhitx and wallhity here for your texture
        h = 0;
        while (h <= HEIGHT && i <= WIDTH)
        {
            if (h <= (HEIGHT - ray->hit->wallhei) / 2)
                    my_mlx_pixel_put(ray,i,h,0x1DE8F2);
                //you can make you texture here for the floor
            else if (h <= ((HEIGHT - ray->hit->wallhei) / 2) + ray->hit->wallhei)
            {
                    if (checkmaphawall(ray,ray->hit->wallhitx,ray->hit->wallhity,50) == 1)
                        my_mlx_pixel_put(ray,i,h,0xEF1DF2);
                    if (checkmaphawall(ray,ray->hit->wallhitx,ray->hit->wallhity + 1,50) == 1)
                        my_mlx_pixel_put(ray,i,h,0xFFB833);
                    if (checkmaphawall(ray,ray->hit->wallhitx + 1,ray->hit->wallhity + 1,50) == 1)
                        my_mlx_pixel_put(ray,i,h,0x8EF21D);
                        // you can make you texture here for the wall
            }
            else
                my_mlx_pixel_put(ray,i,h,0xAB9C61);
                // you can make you texture here for the sky

            h++;
        }
        ray->hit->rayangle += (float)1 / WIDTH;
        // ray->p->playerrotatangl += 0.05;
        // ray->hit->angle_fov  += 0.05;
        if (ray->hit->angle_fov <= 32)
            ray->hit->angle_fov += (float)1 / (WIDTH / 50);
        i++;
    }
}
// void draw_line_with_distance(t_ray *ray, int x, int y, float angle, float length) {
//     // Calculate the endpoint based on the angle and distance
//     float end_x = x + length * cos(angle);
//     float end_y = y + length * sin(angle);

//     int dx = abs((int)end_x - (int)x);
//     int dy = abs((int)end_y - (int)y);
//     int steps = (dy < dx) ? dx : dy; // Use the larger of dx and dy for steps

//     float x_increment = (end_x - x) / steps;
//     float y_increment = (end_y - y) / steps;

//     float current_x = x;
//     float current_y = y;

//     for (int i = 0; i < steps; i++) {
//         my_mlx_pixel_put(ray, (int)current_x, (int)current_y, 0xff0000);
//         current_x += x_increment;
//         current_y += y_increment;
//     }
// }
void draw_line_with_angle(t_ray *ray, float x, float y, float xx, float yy)
{

    int end_x = xx; //+ length * cos(angle);
    int end_y = yy; //+ length * sin(angle);

    int dx = abs(end_x - (int)x);
    int dy = abs(end_y - (int)y);
    int steps = (dy < dx) ? dy : dx;

    float x_increment = (float)(end_x - x) / steps;
    float y_increment = (float)(end_y - y) / steps;

    float current_x = (float)x;
    float current_y = (float)y;

    for (int i = 0; i < steps; i++)
    {
        my_mlx_pixel_put(ray, (int)current_x, (int)current_y, 0xff0000);
        current_x += x_increment;
        current_y += y_increment;
    }
}


// void draw_line_with_distance(t_ray *ray, float x, float y, float distance) {
//     // Calculate the endpoint based on the angle and distance
//     float end_x = x + distance;
//     float end_y = y;

//     // Determine the number of steps based on the distance
//     int num_steps = (int)distance;

//     for (int step = 0; step <= num_steps; step++) {
//         // Calculate the current position
//         float current_x = x + (end_x - x) * step / num_steps;
//         float current_y = y + (end_y - y) * step / num_steps;

//         // Draw a pixel at the current position
//         my_mlx_pixel_put(ray, (int)current_x, (int)current_y, 0xff0000);
//     }
// }


void    wallraycast(t_ray *ray,int x,int y,float rayangel)
{
    int x1;
    int y1;
    int i = 0;


    while (1)
    {
        x1 = x +  (i * cos(rayangel + (PI / 180.0)));
        y1 = y +  (i * sin(rayangel + (PI / 180.0)));
        if (checkmaphawall(ray,x1,y1,10) == 1)
            break;
        i++;
    }
    ray->hit->wallhitx = x1;
    ray->hit->wallhity = y1;
    ray->hit->distance = i;
}
void     drawray(t_ray *ray)
{
    int num_rays = (ray->width);
    float rayangle = ray->p->playerrotatangl - 30 * (PI / 180);
    int i = 0;
    while (i < num_rays)
    {

        wallraycast(ray,(ray->p->px / 50) * 10,(ray->p->py / 50) * 10,rayangle);
        draw_line_with_angle(ray,(ray->p->py / 50) * 10,(ray->p->px / 50) * 10,(ray->hit->wallhity),ray->hit->wallhitx);
    //    draw_line_with_distance(ray,((ray->p->py / 50) * 10) + cos(ray->p->playerrotatangl),((ray->p->px / 50) * 10) + sin(ray->p->playerrotatangl),50);
        rayangle += FOV_ANGLE / num_rays;
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
                ray->p->walkspeed = 3;
                ray->p->turnspeed = 3 * (PI / 180);
                break;
            }
            j++;
        }
        i++;
    }

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
    args->fd = open (av[1], O_RDONLY);
    t_ray *ray = NULL;
    // printf("------------------------------\n");
    ray  = malloc(sizeof(t_ray));
    ray->img = malloc(sizeof(t_img));
    ray->p = malloc(sizeof(t_player));
    ray->hit = malloc(sizeof(t_hitray));
    if (ac == 2 && check_cub(av[1]))
    {
        args = get_map(args);
        check_wall2(args);
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
        // printf("--hei = %d----wid = %d----\n",ray->height,ray->width);
	    ray->mlx = mlx_init(ray);
	    ray->mlx_win = mlx_new_window(ray->mlx,WIDTH,HEIGHT,"Cub3D");
        player_position(ray);
        mlx_hook(ray->mlx_win,2,1L,keyupdate2,ray);
        mlx_hook(ray->mlx_win,3,2L,keyupdate1,ray);
        mlx_hook(ray->mlx_win,17,0,mouse,ray);
        // mlx_hook(ray->mlx_win,3,0L,map,ray);
        mlx_loop_hook(ray->mlx,draw,ray);
	    mlx_loop(ray->mlx);
    }
    else 
        error();
}


#include "cub3d.h"
#include <mlx.h>
#include <signal.h>
void	my_mlx_pixel_put(t_ray *ray, int x, int y, int color)
{
	char	*dst;
    if (x <= 0 || x >= ray->width || y <= 0 || y >= ray->height)
            return ;
	dst = ray->img->addr + (y * ray->img->line_length + x * (ray->img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int checkmaphawall(t_ray *ray, float x, float y)
{
    if (x <= 0 || x >= ray->height || y <= 0 || y >= ray->width)
        return 1;
    int mapGridIndexX = floor(x / 50);
    int mapGridIndexY = floor(y / 50);
    if (ray->map[mapGridIndexX][mapGridIndexY] == '1' || ray->map[mapGridIndexX][mapGridIndexY] == ' ')
        return 1;
     return 0;
    
}


float distamce2point(float x1,float y1,float x2,float y2)
{
    return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void draw_line_with_angle(t_ray *ray, float x, float y, float xx, float yy)
{

    int end_x = xx; //+ length * cos(angle);
    int end_y = yy; //+ length * sin(angle);

    int dx = abs(end_x - (int)x);
    int dy = abs(end_y - (int)y);
    int steps = 10;
    printf("-----%d------\n",steps);

    float x_increment = (float)(end_x - x) / steps;
    float y_increment = (float)(end_y - y) / steps;

    float current_x = (float)x;
    float current_y = (float)y;

    for (int i = 0; i <= steps; i++)
    {
        my_mlx_pixel_put(ray, (int)current_x, (int)current_y, 0xff0000);
        current_x += x_increment;
        current_y += y_increment;
    }
}
void    findwallhit(t_ray *ray,float x,float y,float angle)
{
    float x1;
    float y1;
    float i = 0;

    while (1)
    {
        x1 = x +  5 + (i * cos(angle + ( PI / 180.0)));
        y1 = y +  5 + (i * sin(angle + ( PI / 180.0)));
        if (checkmaphawall(ray,x1,y1) == 1)
            break;
        i++;
    }
    ray->hit->wallhitx = x1;
    ray->hit->wallhity = y1;
    // ray->hit->distance = i;
    // ray->hit->rayangle = ray->p->playerrotatangl;
    ray->hit->walldis = sqrt(pow(ray->hit->wallhitx - ray->p->px,2) + pow(ray->hit->wallhity - ray->p->py,2));
    ray->hit->wallnewdis = ray->hit->walldis * cos(60 * (M_PI / 180));
    ray->hit->wallhei = (50 * ray->height) / ray->hit->wallnewdis;
}
void putpixel(t_ray *ray,float k,float p,int color)
{
    int i = 0;
    int j = 0;

    while (i < 16)
    {
        j = 0;
        while (j < 16)
        {
            my_mlx_pixel_put(ray, k + j,p + i,color);
            j++;
        }
        i++;
    }
}
int	keyupdate2(int keycode, t_ray *ray)
{
	if (keycode == 53)
		exit(0);
        //a == 2
        //d == 53
	else if (keycode == DOWN)
		ray->p->playerwalkdirec = -1;
	else if (keycode == UP)
		ray->p->playerwalkdirec = +1;
	else if (keycode == RIGHT)
		ray->p->playertunrdirec = +1;
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
	return (0);
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
	return (0);
}

int update(t_ray *ray)
{
    float playerx;
    float playery;
    int i = 0;
    int j = 0;
    while (ray->map[i])
    {
        j = 0;
        while (ray->map[i][j])
            j++;
        i++;
    }
    ray->height = i * 50;
    ray->width = j * 50;
    ray->p->playerrotatangl += ray->p->playertunrdirec * ray->p->turnspeed * 0.5;
    float movestep = ray->p->playerwalkdirec * ray->p->walkspeed * 0.5;
        playerx = ray->p->px + cos(ray->p->playerrotatangl) * movestep;
        playery = ray->p->py + sin(ray->p->playerrotatangl) * movestep;

    if ( ray->flag == 1)
    {
        float movesho = ray->p->playerwalkdirec * ray->p->walkspeed * 0.5;
        playerx = ray->p->px + movesho;
        playery = ray->p->py;
        if (!checkmaphawall(ray, playerx, playery))
        {
            ray->p->px = playerx;
        }
    }
   else if (!checkmaphawall(ray,playerx,playery))
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
            my_mlx_pixel_put(ray,(ray->p->py / 50) * 16 + j,(ray->p->px / 50) * 16 + i, 0xff0000);
            j++;
        }
        i++;
    }
    return (0);
}
void    drawwall(t_ray *ray)
{

    int p = 0;
    int k = 0;
    int j = 0;
    int i = 0;
    while (p < (ray->height / 50) * 16)
    {
        j = 0;
        k = 0;
        while (k < (ray->width / 50) * 16)
        {
            if (ray->map[i][j] == '1')
                putpixel(ray,k,p,0xffffff);
            if (ray->map[i][j] == ' ')
                putpixel(ray,k,p,0xffffff);
            j++;
            k += 16;
        } 
        p += 16;
        i++;
    }
}
  
void draw_line(t_ray *ray)
{
    // float num_rays = ray->width;
    int i = 0;
    // while (i < num_rays)
    // {

    //     findwallhit(ray,ray->p->px,ray->p->py,rayangle);
    //     draw_line_with_angle(ray,ray->hit->wallhity,ray->hit->wallhitx,ray->p->py,ray->p->px);
    //     i++;
    // }
    int h = 0;
    i = 0;
    // ray->hit->angle_fov = ray->p->playerrotatangl - (FOV_ANGLE / 2);
    ray->hit->rayangle = ray->p->playerrotatangl;
    float rayangle = ray->p->playerrotatangl - (FOV_ANGLE / 2);
    while (i < ray->width)
    {
        // draw3d(ray);
        h = 0;
        findwallhit(ray,ray->p->px + cos(ray->hit->rayangle +  rayangle) * (M_PI / 180),
            ray->p->py + sin(ray->hit->rayangle +  rayangle) * (M_PI / 180),ray->hit->rayangle);
        //take the wallhitx and wallhity here for your texture
        while (h < ray->height && i < ray->width)
        {
            if (h < (ray->height - ray->hit->wallhei) / 2)
                    my_mlx_pixel_put(ray,i,h,0x0000ff);
                //you can make you texture here for the floor
            else if (h < ((ray->height - ray->hit->wallhei) / 2) + ray->hit->wallhei)
            {
                    if (checkmaphawall(ray,ray->hit->wallhitx,ray->hit->wallhity) == 1)
                        my_mlx_pixel_put(ray,i,h,0x00ffff);
                        //you can make you texture here for the wall
            }
            else
                my_mlx_pixel_put(ray,i,h,0x7a7a7a);
                // you can make you texture here for the sky

            h++;
        }
        ray->hit->rayangle += FOV_ANGLE / ray->width;
        rayangle += FOV_ANGLE / ray->width;
        // if (ray->hit->angle_fov <= 32)
            // ray->hit->angle_fov += FOV_ANGLE / (ray->width / 50);
        i++;
    }
}
// void    drawray(t_ray *ray)
// {
//     int num_rays = 10;
//     float rayangle = ray->p->playerrotatangl - FOV_ANGLE;
//     int i = 0;
//     while (i < num_rays)
//     {

//         findwallhit(ray,(ray->p->px / 50) * 16,(ray->p->py / 50) * 16,rayangle);
//         printf("------%f------\n",ray->hit->wallhity );
//         // draw_line_with_angle(ray,ray->hit->wallhity ,ray->hit->wallhitx ,(ray->p->py / 50) * 16,(ray->p->px / 50) * 16);
//     for (int h = 0; h <= 50; h++)
//     {
//         my_mlx_pixel_put(ray, sin(((ray->p->py / 50) * 16)) + h,cos(((ray->p->px / 50) * 16)) + i, 0xff0000);
//     }
//         rayangle += FOV_ANGLE / num_rays;
//         i++;
//     }
// }
int    draw(t_ray *ray)
{
    update(ray);
    int i = 0;
    int j = 0;
    while (ray->map[i])
    {
        j = 0;
        while (ray->map[i][j])
            j++;
        i++;
    }
    ray->height = i * 50;
    ray->width = j * 50;
    ray->img->img = mlx_new_image(ray->mlx,ray->width,ray->height);
	ray->img->addr = mlx_get_data_addr(ray->img->img, &ray->img->bits_per_pixel, &ray->img->line_length,&ray->img->endian);
    draw_line(ray);
    drawplayer(ray);
    drawwall(ray);
    // drawray(ray);
    // draw3d(ray);
    mlx_put_image_to_window(ray->mlx, ray->mlx_win, ray->img->img, 0, 0);
    mlx_destroy_image(ray->mlx,ray->img->img);
    return (0);
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
            if (ray->map[i][j] == 'N')
            {
                ray->map[i][j] = '0';
                ray->p->px = i * 50;
                ray->p->py = j * 50;
                ray->p->playerrotatangl = FOV_ANGLE;
                ray->p->playertunrdirec = 0;
                ray->p->playerwalkdirec = 0;
                ray->p->walkspeed = 10;
                ray->p->turnspeed = 10 * (PI / 180);
                break;
            }
            j++;
        }
        i++;
    }

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
        // printf("\033[32m OK!\n");
        // draw(args->copy);
        ray->map = args->copy;
        int i = 0;
        int j = 0;
        while (ray->map[i])
        {
            j = 0;
            // printf("---%s----\n",ray->map[i]);
            while (ray->map[i][j])
                j++;
            i++;
        }
        int height = i * 50;
        int width = j * 50;
	    ray->mlx = mlx_init(ray);
	    ray->mlx_win = mlx_new_window(ray->mlx,width,height, "Cub3D");
        player_position(ray);
        mlx_hook(ray->mlx_win,2,0L,keyupdate2,ray);
        mlx_hook(ray->mlx_win,3,0L,keyupdate1,ray);
        mlx_loop_hook(ray->mlx,draw,ray);
	    mlx_loop(ray->mlx);
    }
    else 
        error();
}

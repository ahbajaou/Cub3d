#include "cub3d.h"

// void get_image(t_args *args, t_ray *ray, int j, int i)
// {
//     int	x;
// 	int	y;

// 	x = so_long->width;
// 	y = so_long->height;
// 	args->img_1 = mlx_xpm_file_to_image(args->mlx, "textures/wall.xpm", &x, &y);
// 	if (!s_win->img)
// 		error();
// 	mlx_put_image_to_window(s_win->mlx, s_win->win, s_win->img, j, i);
// 	mlx_destroy_image(s_win->mlx, s_win->img);
// }
void get_image(t_ray *ray, int x, int y)
{
	// ray->img = malloc(sizeof(t_ray));
	ray->hit->textwid = y;
	ray->hit->texthei = x;
	//------------------------------------//
	 ray->img[0].img2 = mlx_xpm_file_to_image(ray->mlx,ray->no, &ray->img[0].texthei, &ray->img[0].textwid);
	ray->img[0].addr2 = mlx_get_data_addr(ray->img[0].img2, &ray->img[0].bits_per_pixel2, &ray->img[0].line_length2, &ray->img[0].endian2);
	ray->img[1].img2 = mlx_xpm_file_to_image(ray->mlx,ray->so, &ray->img[1].texthei, &ray->img[1].textwid);
	ray->img[1].addr2 = mlx_get_data_addr(ray->img[1].img2, &ray->img[1].bits_per_pixel2, &ray->img[1].line_length2, &ray->img[1].endian2);
	ray->img[2].img2 = mlx_xpm_file_to_image(ray->mlx,ray->we, &ray->img[2].texthei, &ray->img[2].textwid);
	ray->img[2].addr2 = mlx_get_data_addr(ray->img[2].img2, &ray->img[2].bits_per_pixel2, &ray->img[2].line_length2, &ray->img[2].endian2);
	ray->img[3].img2 = mlx_xpm_file_to_image(ray->mlx,ray->ea, &ray->img[3].texthei, &ray->img[3].textwid);
	ray->img[3].addr2 = mlx_get_data_addr(ray->img[3].img2, &ray->img[3].bits_per_pixel2, &ray->img[3].line_length2, &ray->img[3].endian2);
	//--------------------------------------------------------//
    ray->img->img2 = mlx_xpm_file_to_image(ray->mlx,ray->we, &ray->hit->texthei, &ray->hit->textwid);
	ray->img->addr2 = mlx_get_data_addr(ray->img->img2, &ray->img->bits_per_pixel2, &ray->img->line_length2, &ray->img->endian2);
	// printf("-=-=-0=-=->%s\n",ray->img->addr );
}

int colors_img(t_ray *ray, int x, int y)
{
	// printf("--------x == %d-----y == %d---\n",x,y);
	char *str;
	// str = ft_strdup("");
	//  if (ray->deriction == 1)
	if (x < 0 || y < 0)
		return 0;
	str = ray->img->addr2 + (y * ray->img->line_length2 + x * (ray->img->bits_per_pixel2 / 8));
		// printf("|%d|\n",*(unsigned int *)str);
		// exit(0);
		// else
		// return(*(int *)str);
	return(*(int *)str);
}
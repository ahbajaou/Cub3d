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
	printf("-=-=-=-=-=->%s\n", ray->ea);
    ray->img->img2 = mlx_xpm_file_to_image(ray->mlx,ray->ea, &x, &y);

	ray->img->addr2 = mlx_get_data_addr(ray->img->img2, &ray->img->bits_per_pixel2, &ray->img->line_length2, &ray->img->endian2);
	// printf("-=-=-0=-=->%s\n",ray->img->addr );
}

int colors_img(t_ray *ray, int x, int y)
{
	// printf("--------x == %d-----y == %d---\n",x,y);
	char *str;
	// str = ft_strdup("");
	//  if (ray->deriction == 1)
		str = ray->img->addr2 + (y * ray->img->line_length2 + x * (ray->img->bits_per_pixel2 / 8));
		// printf("|%d|\n",*(unsigned int *)str);
		// exit(0);
		// else
		// return(*(int *)str);
	return(*(int *)str);
}
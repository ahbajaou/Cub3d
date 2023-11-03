/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: himejjad <himejjad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 07:19:09 by himejjad          #+#    #+#             */
/*   Updated: 2023/11/03 08:31:00 by himejjad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <mlx.h>
#include <math.h>
# include <ctype.h>
#include <fcntl.h>
#include "get_next_line.h"
#define BUFFER_SIZE 1
#define PI 3.1415926
#define M_PI_2 1.57079632679489661923
#define TWO_PI 6.28318530
#define UP 119
#define DOWN 115
#define RIGHT_A 100
#define LEFT_D 97
#define RIGHT  65363
#define LEFT 65361
#define FRAM 124
#define US 0,5
#define AS 1,5
#define HEIGHT 850
#define WIDTH 1000
#define FOV_ANGLE 60 * (PI / 180)

typedef struct	s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct t_hitray
{
    float rayangle;
    float wallhitx;
    float wallhity;
    float distance;
    float      angle_fov;
    float     wallhittop;
    float     wallhitboton;
    float     wallhitheight;
    float     wallhei;
    float     walldis;
    float     wallnewdis;

} t_hitray;

typedef struct t_player
{
    float     px;
    float     py;
    float     playerwalkdirec;
    float     playertunrdirec;
    float     playerrotatangl;
    float     walkspeed;
    float     turnspeed;
}t_player;

typedef struct t_ray
{
    void	*mlx;
    void	*mlx_win;
    char    **map;
    float     wallhitx;
    float     wallhity;
    float     wallhittop;
    float     wallhitboton;
    float     wallhitheight;
    float       distance;
     char *we;
    char *no;
    char *ea;
    char *so;
    int floor_r;
    int floor_g;
    int floor_b;
    int cell_r;
    int cell_g;
    int cell_b;
    int flagmap;
    int flag;
    int height;
    int width;
    t_img *img;
    t_player *p;
    t_hitray *hit;

} t_ray;

typedef struct s_args
{
    char **argv;
    char **av;
    char **copy;
    char **rgb;
    char *str;
    int fd;
    int xp;
    char **copy2;
    int yp;
    int height;
    int width; 
    char *floor;
    char *cell;
    char *we;
    char *no;
    char *ea;
    char *so;
    int floor_r;
    int floor_g;
    int floor_b;
    int cell_r;
    int cell_g;
    int cell_b;
    
}t_args;

void	error(void);
char	*get_next_line(int fd);
t_args * get_map(t_args *args);
char	**ft_split(char *s, char c);
int	count_lines(char **map);
int	check_cub(char *file);
void	check_wall2(t_args *args);
char	*ft_strdup(const char *s1);
void get_image(t_ray *ray, int x, int y);
int colors_img(t_ray *ray, int x, int y);
#endif
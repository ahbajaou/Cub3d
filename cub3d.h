/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: himejjad <himejjad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 07:19:09 by himejjad          #+#    #+#             */
/*   Updated: 2023/11/10 19:57:17 by himejjad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "get_next_line.h"
# include <ctype.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define BUFFER_SIZE 1
# define PI 3.1415926
# define TWO_PI 6.28318530
# define UP 13
# define DOWN 1
# define LEFT_D 0
# define RIGHT_A 2
# define LEFT 123
# define RIGHT 124
# define HEIGHT 1000
# define WIDTH 1000

typedef struct s_img
{
	void		*img;
	char		*addr;
	void		*mlx;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	void		*img1;
	char		*addr1;
	int			bits_per_pixel1;
	int			line_length1;
	int			endian1;
	void		*img2;
	char		*addr2;
	int			bits_per_pixel2;
	int			line_length2;
	int			endian2;
	void		*img3;
	char		*addr3;
	int			bits_per_pixel3;
	int			line_length3;
	int			endian3;
	void		*img4;
	char		*addr4;
	int			bits_per_pixel4;
	int			line_length4;
	int			endian4;
	int			textwid;
	int			texthei;
}				t_img;

typedef struct t_hitray
{
	float		rayangle;
	int			direction;
	float		angle_fov;
	float		wallhei;
	float		walldis;
	float		wallhitx;
	float		wallhity;
	float		wallnewdis;
	int			ofx;
	int			textwid;
	int			texthei;

}				t_hitray;

typedef struct t_player
{
	float		px;
	float		py;
	float		playerwalkdirec;
	float		playertunrdirec;
	float		playerrotatangl;
	float		walkspeed;
	float		turnspeed;
	float		playerx;
	float		playery;
	float		movestep;
}				t_player;

typedef struct t_ray
{
	void		*mlx;
	void		*mlx_win;
	char		**map;
	float		distance;
	char		*we;
	char		*no;
	char		*ea;
	char		*so;
	int			height;
	int			width;
	int			floor_r;
	int			floor_g;
	int			floor_b;
	int			cell_r;
	int			cell_g;
	int			cell_b;
	int			flagmap;
	char		*str;
	int			flag;
	int			virti;
	int			deriction;
	t_img		*img;
	t_player	*p;
	t_hitray	*hit;

}				t_ray;

typedef struct s_args
{
	char		**argv;
	char		**av;
	char		**copy;
	char		**rgb;
	char		*str;
	int			fd;
	int			xp;
	char		**copy2;
	int			yp;
	int			height;
	int			width;
	char		*floor;
	char		*cell;
	char		*we;
	char		*no;
	char		*ea;
	char		*so;
	int			floor_r;
	int			floor_g;
	int			floor_b;
	int			cell_r;
	int			cell_g;
	int			cell_b;
}				t_args;

//-----------------------raycast----------------------------//
void			my_mlx_pixel_put(t_ray *ray, int x, int y, int color);
int				checkmaphawall(t_ray *ray, int x, int y, int size);
float			distamce2point(float x1, float y1, float x2, float y2);
int				keyupdate2(int keycode, t_ray *ray);
int				keyupdate1(int keycode, t_ray *ray);
int				update(t_ray *ray);
int				drawplayer(t_ray *ray);
void			putpixel(t_ray *ray, int x, int y, int color);
void			drawwall(t_ray *ray);
int				get_clr_rgb(int r, int g, int b);
void			virti_or_hori(t_ray *ray);
void			findwallhit(t_ray *ray, float x, float y, float angle);
int				finddirection(t_ray *ray);
int				getofx(t_ray *ray);
void			draw3d_2(t_ray *ray, int i);
void			draw3d(t_ray *ray);
void			draw_ray_with_distance(t_ray *ray, float x, float y,
					float angle);
void			drawray(t_ray *ray);
int				draw(t_ray *ray);
void			get_rot(char c, t_ray *ray, int i, int j);
void			player_position(t_ray *ray);
int				mouse(void);
void			get_sizeofmap(t_ray *ray);
void			raycasting(t_ray *ray);
void			exchange(t_ray *ray, t_args *args);
//----------------------parsing--------------------
void			error(void);
char			*get_next_line(int fd);
t_args			*get_map(t_args *args);
char			**ft_split(char *s, char c);
int				count_lines(char **map);
int				check_cub(char *file);
char			*ft_strdup(const char *s1);
void			get_image(t_ray *ray);
void			check_wall2(t_args *args);
int				colors_img(t_ray *ray, int x, int y);
void			check_n_w_s_e(t_args *args);
void			skip_space(t_args *args);
void			skip_space_norm(t_args *args, int j, int i);
void			skip_norm_n(t_args *args, int j, int i, char c);
int				ft_isalnum(int c);
int				check_face_norm(t_args *args, int j, int i, int count);
void			check_face(t_args *args);
int				skip_space_2(t_args *args, int j, int i);
void			get_deriction_norm(t_args *args, int j, int i);
void			get_deriction(t_args *args);
void			check_space_2(t_args *args);
void			check_xpm(char *file);
void			free_rgb(t_args *args);
void			norm_space(t_args *args, int j, int i);
void			norm_skip_space(t_args *args, int j, int i);
#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalkhidi <yalkhidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 19:40:22 by omaimaqaroo       #+#    #+#             */
/*   Updated: 2025/12/04 17:29:14 by yalkhidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "mlx.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdint.h>

# define SCREEN_WIDTH 1200
# define SCREEN_HEIGHT 800
# define TEX_WIDTH 256
# define TEX_HEIGHT 256
# define MAP_WIDTH 24
# define MAP_HEIGHT 24

# define ESC 53
# define KEY_7 89
# define KEY_8 91
# define KEY_W 13
# define KEY_S 1
# define KEY_A 0
# define KEY_D 2
# define KEY_RIGHT_ARROW 124
# define KEY_LEFT_ARROW 123
# define MOVE_SPEED 0.05
# define ROT_SPEED  0.05

//=====================Row list struct==========================
typedef struct s_row_list
{
	int					*row;
	int					size;
	struct s_row_list	*next;
}						t_row_list;

//=====================Resources struct==========================
typedef struct t_resources
{
	char				**tex_path;
	int					floor_rgb[3];
	int					ceil_rgb[3];
	int					**map;
	t_row_list			*rowlist;
	int					map_height;
	int					map_width;
}						t_resources;

typedef struct s_player
{
	char facing_dir; // 0 - North, 1 - East, 2 - South, 3 - West
	double	pos_x; // player's x position
	double	pos_y; //player's y position
	double	dir_x; // player's direction vector x component
	double	dir_y; // player's direction vector y component
	double	plane_x; // camera plane x component perpendicular to dir
	double	plane_y; // camera plane y component 
}	t_player;

typedef struct s_map
{
	int		width;
	int		height;
	char	**grid;
}	t_map;

typedef struct s_ray
{
	double	ray_dir_x;// direction of the ray x component
	double	ray_dir_y;// direction of the ray along the y axis (up down)
	double	side_dist_x; // the initial distance from the ray to the next x side
	double	side_dist_y; //
	double	delta_dist_x;// how far the ray must travel to cross one grid square
	double	delta_dist_y;//
	double	wall_dist; //
	int		map_x;// 
	int		map_y;//
	int		step_x; // which direction the ray is moving x axis(left, right)
	int		step_y; // which direction the ray is moving y axis (up, down)
	int		hit; // was a wall hit during dda
	int		side; //which wall was hit vertical (0) or horizontal (1)
	int		line_length;
	int		draw_start;
	int		draw_end;
	double	wall_x;
	int		tex_id;
	int 	tex_x;
	int 	tex_y;
	double	tex_pos;
	double	step;
}	t_ray;

typedef struct s_screen
{
	// int width;
	// int height;
	void	*mlx; //DONE
	void	*win; //DONE
	void	*img; //DONE
	char	*buf; // image buffer, a pointer tho the first byte of the image
	int		pix_bits; // bits per pixel
	int		l_bytes; // line length
	int		endian;	//
	int		buf_size;
}	t_screen;

typedef struct s_texture
{
	void	*img;
	char	*buf;
	int		width;
	int		height;
	int		pix_bits;
	int		l_bytes;
	int		endian;
}	t_texture;

typedef struct s_game
{
	t_player	player;
	// t_map map;
	t_ray		ray;
	t_screen	screen;
	t_resources	resources;
	t_texture	textures[4]; // North, East, South, West
	long		time;
	long		old_time;
	double		move_speed;
	double		rotate_speed;

}	t_game;

//=====================Function prototypes==========================
int						parse(int argc, char *argv[], t_resources *resources);
int						assign_rgb(int *rgb, char *str);
int						add_mapline(char *str, t_resources *resources,
							int done);
int						add_rownode(t_resources *resources, t_row_list *node);
void					clean_resources(t_resources *resources);
int						list_to_matrix(t_resources *resources);
int						check_map(t_resources *resources);
int						check_char(int c, int check);
int						additional_check(t_resources *resources);
void					init_resources(t_resources *resources);

int						clean_and_print_error(char *msg, t_resources *resources,
							int ret_val);
void					exit_game(char *msg, t_game *game);
void					init_game(t_game *game);
int						calculate(t_game *game);
int						key_handlers(int keycode, t_game *game);
int						close_window(t_game *game);
int	calculate(t_game *game);
long int	get_time(void);
int get_tex_color(t_game *game, int tex_id, int tex_x, int tex_y);
uint32_t	get_hex_from_rgb(unsigned char r, unsigned char g, unsigned char b);
void	put_pixel(t_game *game, int x, int y, int color);
void	plot(int x, int y, t_game *d, int color);
void	draw_background(t_game *game);
#endif

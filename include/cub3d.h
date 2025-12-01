/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalkhidi <yalkhidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 19:40:22 by omaimaqaroo       #+#    #+#             */
/*   Updated: 2025/12/01 18:12:18 by yalkhidi         ###   ########.fr       */
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
	double	ray_dir_x;
	double	ray_dir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
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

typedef struct s_game
{
	t_player	player;
	// t_map map;
	t_ray ray;
	t_screen	screen;
	t_resources	resources;
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

int						clean_and_print_error(char *msg, t_resources *resources, int ret_val);
void	init_game(t_game *game);

#endif

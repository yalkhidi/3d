/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalkhidi <yalkhidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 19:40:22 by omaimaqaroo       #+#    #+#             */
/*   Updated: 2025/11/27 17:45:06 by yalkhidi         ###   ########.fr       */
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

//=====================Texture struct==========================
typedef struct s_texture
{
	int					height;
	int					width;
	void				*img;
	char				*path;
	char				*buf;
	int					pix_bits;
	int					l_bytes;
	int					endi;
}						t_texture;

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

//=====================Data struct==========================
typedef struct s_data
{
	void				*mlx;
	void				*win;
	int					pix_bits;
	int					l_bytes;
	int					endi;
	void				*img;
	char				*buf;
	int					buf_size;
	double				pos_x;
	double				pos_y;
	double				dir_x;
	double				dir_y;
	double				plane_x;
	double				plane_y;
	long int			time;
	long int			old_time;
	double				camera_x;
	double				ray_dir_x;
	double				ray_dir_y;
	int					map_x;
	int					map_y;
	double				side_dist_x;
	double				side_dist_y;
	double				delta_dist_x;
	double				delta_dist_y;
	double				perp_wall_dist;
	int					step_x;
	int					step_y;
	double				step;
	int					side;
	int					line_height;
	int					view_shift;
	int					draw_start;
	int					draw_end;
	int					tex_num;
	double				wall_x;
	int					tex_x;
	long double			frame_time;
	double				move_speed;
	double				rot_speed;
	int					floor_color;
	int					ceiling_color;
	t_resources			*resources;
	t_texture			**texture;
}						t_data;

void					init(t_data *data, t_resources *resources);
void					render(t_data *data);
void					run_dda(t_data *data);
void					get_move_rot_speeds(t_data *data);
void					plot(int x, int y, t_data *data, int color);
void					draw_floor_and_ceiling(t_data *data);
void					update_vars(int x, t_data *data);
void					draw_strip(t_data *data, int x);
int						close_window(t_data *data);
int						key_handler(int key, t_data *data);
void					error_msg(char *str, t_data *dataata);
long int				get_time(t_data *data);
void					free_all(t_data *data);
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
// void					rotate_right(t_data *data, double rad);
// void					rotate_left(t_data *data, double rad);
void					rotate(t_data *data, double rad, char *rotate_side);
uint32_t				get_hex_from_rgb(unsigned char r, unsigned char g,
							unsigned char b);
t_texture				**init_texture(t_data *data, t_resources *resources);

#endif

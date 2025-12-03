/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalkhidi <yalkhidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 19:38:24 by omaimaqaroo       #+#    #+#             */
/*   Updated: 2025/12/03 18:48:11 by yalkhidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_resources(t_resources *resources)
{
	int	i;

	resources->tex_path = (char **)malloc(sizeof(char *) * 4);
	i = 0;
	while (i < 4)
	{
		resources->tex_path[i] = NULL;
		i++;
	}
	i = 0;
	while (i < 3)
	{
		resources->floor_rgb[i] = -1;
		resources->ceil_rgb[i] = -1;
		i++;
	}
	resources->map = NULL;
	resources->rowlist = NULL;
	resources->map_height = 0;
	resources->map_width = 0;
}

void	init_player_position(t_game *game)
{
	int	i;
	int	j;
	int	l;

	i = 0;
	while (++i < game->resources.map_height - 1)
	{
		j = 0;
		while (++j < game->resources.map_width - 1)
		{
			l = (char)game->resources.map[i][j];
			if (l == 'N' || l == 'E' || l == 'S' || l == 'W')
			{
				game->player.pos_x = j + 0.5;
				game->player.pos_y = i + 0.5;
				return ;
			}
		}
	}
}

void	init_player_orientation(t_game *game)
{
	char	c;

	c = game->resources.map[(int)game->player.pos_y][(int)game->player.pos_x];
	if (c == 'N')
	{
		game->player.dir_x = 0;
		game->player.dir_y = -1;
		game->player.plane_x = 0.66;
		game->player.plane_y = 0;
	}
	if (c == 'S')
	{
		game->player.dir_x = 0;
		game->player.dir_y = 1;
		game->player.plane_x = -0.66;
		game->player.plane_y = 0;
	}
	if (c == 'E')
	{
		game->player.dir_x = 1;
		game->player.dir_y = 0;
		game->player.plane_x = 0;
		game->player.plane_y = 0.66;
	}
	if (c == 'W')
	{
		game->player.dir_x = -1;
		game->player.dir_y = 0;
		game->player.plane_x = 0;
		game->player.plane_y = -0.66;
	}
}

void	exit_game(char *msg, t_game *game)
{
	if (msg)
		ft_putendl_fd(msg, 2);
	clean_resources(&game->resources);
	exit(0);
}
unsigned long	get_time(void)
{
	struct timeval	time;
	unsigned long	time_in_ms;

	gettimeofday(&time, NULL);
	time_in_ms = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (time_in_ms);
}
void init_textures(t_game *game)
{
	int i;

	const char *tex_files[4] = {
		game->resources.tex_path[0], // North
		game->resources.tex_path[1], // East
		game->resources.tex_path[2], // South
		game->resources.tex_path[3]  // West
	};
	i = 0;
	while (i < 4)
	{
		game->textures[i].img = mlx_xpm_file_to_image(game->screen.mlx,
				(char *)tex_files[i],
				&game->textures[i].width,
				&game->textures[i].height);
		if (!game->textures[i].img)
			exit_game("Error loading texture image", game);

		game->textures[i].addr = mlx_get_data_addr(game->textures[i].img,
				&game->textures[i].bpp,
				&game->textures[i].line_len,
				&game->textures[i].endian);
		if (!game->textures[i].addr)
			exit_game("Error getting texture image address", game);
		i++;
	}
}

void	init_game(t_game *game)
{
	game->screen.mlx = mlx_init();
	if (!game->screen.mlx)
		exit_game("Error initializing MLX", game);
	game->screen.win = mlx_new_window(game->screen.mlx, SCREEN_WIDTH,
			SCREEN_HEIGHT, "CUB3D");
	if (!game->screen.win)
		exit_game("Error creating window", game);
	game->screen.img = mlx_new_image(game->screen.mlx, SCREEN_WIDTH,
			SCREEN_HEIGHT);
	if (!game->screen.img)
		exit_game("Error creating image", game);
	game->screen.buf = mlx_get_data_addr(game->screen.img,
			&game->screen.pix_bits, &game->screen.l_bytes,
			&game->screen.endian);
	if (!game->screen.buf)
		exit_game("Error getting image buffer", game);
	init_player_position(game);
	init_player_orientation(game);
	init_textures(game);
	game->time = get_time();
}
void	put_pixel(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
		return;

	dst = game->screen.buf
		+ (y * game->screen.l_bytes + x * (game->screen.pix_bits / 8));

	*(unsigned int *)dst = color;
}

int get_tex_color(t_game *game, int tex_id, int tex_x, int tex_y)
{
	char	*tex_addr;
	int		color;
	int		line_len;
	int		bpp;

	tex_addr = game->textures[tex_id].addr;
	line_len = game->textures[tex_id].line_len;
	bpp = game->textures[tex_id].bpp;

	color = *(unsigned int *)(tex_addr + (tex_y * line_len + tex_x * (bpp / 8)));
	return (color);
}

int	calculate(t_game *game)
{
	int	x;
	double	camera_x;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		ft_bzero(game->screen.buf, SCREEN_HEIGHT * game->screen.l_bytes);
		camera_x = 2.0 * x / (double)SCREEN_WIDTH - 1;
		game->ray.ray_dir_x = game->player.dir_x + game->player.plane_x
			* camera_x;
		game->ray.ray_dir_y = game->player.dir_y + game->player.plane_y
			* camera_x;
		
		game->ray.map_x = (int)game->player.pos_x;
		game->ray.map_y = (int)game->player.pos_y;
	
		if (game->ray.ray_dir_x == 0)
			game->ray.delta_dist_x = 1e30;
		else
			game->ray.delta_dist_x = fabs(1/ game->ray.ray_dir_x);
		if (game->ray.ray_dir_y == 0)
			game->ray.delta_dist_y = 1e30;
		else
			game->ray.delta_dist_y = fabs(1/ game->ray.ray_dir_y);
		
		if (game->ray.ray_dir_x < 0)
		{
			game->ray.step_x = -1;
			game->ray.side_dist_x = (game->player.pos_x - game->ray.map_x) * game->ray.delta_dist_x;
		}
		else
		{
			game->ray.step_x = 1;
			game->ray.side_dist_x = (game->ray.map_x + 1.0 - game->player.pos_x) * game->ray.delta_dist_x;
		}
		
		if (game->ray.ray_dir_y < 0)
		{
			game->ray.step_y = -1;
			game->ray.side_dist_y = (game->player.pos_y - game->ray.map_y) * game->ray.delta_dist_y;
		}
		else
		{
			game->ray.step_y = 1;
			game->ray.side_dist_y = (game->ray.map_y + 1.0 - game->player.pos_y) * game->ray.delta_dist_y;
		}
		
		game->ray.hit = 0;
		while(game->ray.hit == 0)
		{
			if (game->ray.side_dist_x < game->ray.side_dist_y)
			{
				game->ray.side_dist_x += game->ray.delta_dist_x;
				game->ray.map_x += game->ray.step_x;
				game->ray.side = 0;
			}
			else
			{
				game->ray.side_dist_y += game->ray.delta_dist_y;
				game->ray.map_y += game->ray.step_y;
				game->ray.side = 1;
			}
			if (game->resources.map[game->ray.map_y][game->ray.map_x] == '1')
				game->ray.hit = 1;
		}
		
		if (game->ray.side == 0)
			game->ray.wall_dist = (game->ray.side_dist_x - game->ray.delta_dist_x);
		else
			game->ray.wall_dist = game->ray.side_dist_y - game->ray.delta_dist_y;
		
		int line_length = (int)(SCREEN_HEIGHT / game->ray.wall_dist);
		int draw_start;
		int draw_end;

		draw_start = -line_length / 2 + SCREEN_HEIGHT / 2;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = line_length / 2 + SCREEN_HEIGHT / 2;
		if (draw_end > SCREEN_HEIGHT )
			draw_end = SCREEN_HEIGHT - 1;
		//Drawing
		int tex_id;
		//North 0 East 1 South 2 West 3
		if (game->ray.side == 0)
		{
			if (game->ray.ray_dir_x > 0)
				tex_id = 1;
			else
				tex_id = 3;
		}
		else
		{
			if (game->ray.ray_dir_y > 0)
				tex_id = 2;
			else
				tex_id = 0;
		}

		double wall_x;
		if (game->ray.side == 0)
			wall_x = game->player.pos_y + game->ray.wall_dist * game->ray.ray_dir_y;
		else
			wall_x = game->player.pos_x + game->ray.wall_dist * game->ray.ray_dir_x;
		wall_x -= floor(wall_x);
		
		int tex_x;
		tex_x = (int)(wall_x * (double)TEX_WIDTH);
		if (game->ray.side == 0 && game->ray.ray_dir_x > 0)
			tex_x = TEX_WIDTH - tex_x - 1;
		if (game->ray.side == 1 && game->ray.ray_dir_y < 0)
			tex_x = TEX_WIDTH - tex_x - 1;
		
		double step;
		double tex_pos;
		step = 1.0 * TEX_HEIGHT/ line_length;
		tex_pos = (draw_start - SCREEN_HEIGHT / 2 + line_length / 2) * step;
		
		int y;
		int tex_y;
		y = draw_start;
		while(y < draw_end)
		{
			tex_y = (int)tex_pos;
			if (tex_y < 0)
				tex_y = 0;
			if (tex_y >= TEX_HEIGHT)
				tex_y = TEX_HEIGHT - 1;

			tex_pos += step;
			
			int color = get_tex_color(game, tex_id, tex_x, tex_y);
			put_pixel(game, x, y, color);
			y++;
		}
		game->old_time = game->time;
		game->time = get_time();;
		long frame_time = (game->time - game->old_time) / 1000;
		game->move_speed = frame_time * 5.0;
		game->rotate_speed = frame_time * 3.0;
		x++;
	}
	mlx_put_image_to_window(game->screen.mlx, game->screen.win, game->screen.img, 0, 0);
	return (0);
}

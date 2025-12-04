/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalkhidi <yalkhidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 15:06:33 by yalkhidi          #+#    #+#             */
/*   Updated: 2025/12/04 17:58:56 by yalkhidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_side_distance(t_game *game)
{
	if (game->ray.ray_dir_x < 0)
	{
		game->ray.step_x = -1;
		game->ray.side_dist_x = (game->player.pos_x - game->ray.map_x)
			* game->ray.delta_dist_x;
	}
	else
	{
		game->ray.step_x = 1;
		game->ray.side_dist_x = (game->ray.map_x + 1.0 - game->player.pos_x)
			* game->ray.delta_dist_x;
	}
	if (game->ray.ray_dir_y < 0)
	{
		game->ray.step_y = -1;
		game->ray.side_dist_y = (game->player.pos_y - game->ray.map_y)
			* game->ray.delta_dist_y;
	}
	else
	{
		game->ray.step_y = 1;
		game->ray.side_dist_y = (game->ray.map_y + 1.0 - game->player.pos_y)
			* game->ray.delta_dist_y;
	}
}

void	set_ray(t_game *game, int x)
{
	double	camera_x;

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
		game->ray.delta_dist_x = fabs(1 / game->ray.ray_dir_x);
	if (game->ray.ray_dir_y == 0)
		game->ray.delta_dist_y = 1e30;
	else
		game->ray.delta_dist_y = fabs(1 / game->ray.ray_dir_y);
	set_side_distance(game);
}

void	run_dda(t_game *game)
{
	game->ray.hit = 0;
	while (game->ray.hit == 0)
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
		if (game->resources.map[game->ray.map_x][game->ray.map_y] == '1')
			game->ray.hit = 1;
	}
}

void	set_wall(t_game *game)
{
	if (game->ray.side == 0)
		game->ray.wall_dist = (game->ray.side_dist_x - game->ray.delta_dist_x);
	else
		game->ray.wall_dist = game->ray.side_dist_y - game->ray.delta_dist_y;
	if (game->ray.side == 0)
		game->ray.wall_x = game->player.pos_y
			+ game->ray.wall_dist * game->ray.ray_dir_y;
	else
		game->ray.wall_x = game->player.pos_x
			+ game->ray.wall_dist * game->ray.ray_dir_x;
	game->ray.wall_x -= floor(game->ray.wall_x);
	game->ray.line_length = (int)(SCREEN_HEIGHT / game->ray.wall_dist);
	game->ray.draw_start = -game->ray.line_length / 2 + SCREEN_HEIGHT / 2;
	if (game->ray.draw_start < 0)
		game->ray.draw_start = 0;
	game->ray.draw_end = game->ray.line_length / 2 + SCREEN_HEIGHT / 2;
	if (game->ray.draw_end > SCREEN_HEIGHT)
		game->ray.draw_end = SCREEN_HEIGHT - 1;
}

void	set_texture_id(t_game *game)
{
	if (game->ray.side == 0)
	{
		if (game->ray.ray_dir_x > 0)
			game->ray.tex_id = 1;
		else
			game->ray.tex_id = 3;
	}
	else
	{
		if (game->ray.ray_dir_y > 0)
			game->ray.tex_id = 2;
		else
			game->ray.tex_id = 0;
	}
	game->ray.tex_x = (int)(game->ray.wall_x * (double)TEX_WIDTH);
	if (game->ray.side == 0 && game->ray.ray_dir_x > 0)
		game->ray.tex_x = TEX_WIDTH - game->ray.tex_x - 1;
	if (game->ray.side == 1 && game->ray.ray_dir_y < 0)
		game->ray.tex_x = TEX_WIDTH - game->ray.tex_x - 1;
}

void	draw_texture(t_game *game, int x)
{
	int	color;
	// int pix;
	int	y;

	set_wall(game);
	set_texture_id(game);
	game->ray.step = 1.0 * TEX_HEIGHT / game->ray.line_length;
	game->ray.tex_pos = (game->ray.draw_start - SCREEN_HEIGHT / 2
			+ game->ray.line_length / 2) * game->ray.step;
	y = game->ray.draw_start;
	while (y < game->ray.draw_end)
	{
		game->ray.tex_y = (int)game->ray.tex_pos;
		if (game->ray.tex_y < 0)
			game->ray.tex_y = 0;
		if (game->ray.tex_y >= TEX_HEIGHT)
			game->ray.tex_y = TEX_HEIGHT - 1;
		game->ray.tex_pos += game->ray.step;
		color = get_tex_color(game, game->ray.tex_id,
				game->ray.tex_x, game->ray.tex_y);
		put_pixel(game, x, y, color);
		// pix = y * game->screen.l_bytes + x * 4;
		// game->screen.buf[pix + 0] = game->textures[game->ray.tex_id].buf[game
		// 	->textures[game->ray.tex_id].l_bytes * game->ray.tex_y
		// 	+ game->ray.tex_x * 4];
		// game->screen.buf[pix + 1] = game->textures[game->ray.tex_id].buf[game
		// 	->textures[game->ray.tex_id].l_bytes * game->ray.tex_y
		// 	+ game->ray.tex_x * 4 + 1];
		// game->screen.buf[pix + 2] = game->textures[game->ray.tex_id].buf[game
		// 	->textures[game->ray.tex_id].l_bytes * game->ray.tex_y
		// 	+ game->ray.tex_x * 4 + 2];
		// game->screen.buf[pix + 3] = game->textures[game->ray.tex_id].buf[game
		// 	->textures[game->ray.tex_id].l_bytes * game->ray.tex_y
		// 	+ game->ray.tex_x * 4 + 3];
		y++;
	}
}

void	update_times(t_game *game)
{
	double	frame_time;

	game->old_time = game->time;
	game->time = get_time();
	frame_time = (game->time - game->old_time) / 1000.0;
	game->move_speed = frame_time * 5.0;
	game->rotate_speed = frame_time * 3.0;
}

int	calculate(t_game *game)
{
	int	x;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		set_ray(game, x);
		run_dda(game);
		draw_texture(game, x);
		x++;
	}
	update_times(game);
	mlx_put_image_to_window(game->screen.mlx, game->screen.win,
		game->screen.img, 0, 0);
	return (0);
}

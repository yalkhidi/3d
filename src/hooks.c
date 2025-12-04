/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalkhidi <yalkhidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 18:48:52 by yalkhidi          #+#    #+#             */
/*   Updated: 2025/12/04 18:01:55 by yalkhidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	key_w_s(int key, t_game *game)
{
	if (key == KEY_W)
	{
		if (game->resources.map[(int)(game->player.pos_x + game->player.dir_x
				* game->move_speed)][(int)game->player.pos_y] != '1')
			game->player.pos_x += game->player.dir_x * game->move_speed;
		if (game->resources.map[(int)game->player.pos_x][(int)(game->player.pos_y + game->player.dir_y
				* game->move_speed)] != '1')
			game->player.pos_y += game->player.dir_y * game->move_speed;
	}
	if (key == KEY_S)
	{
		if (game->resources.map[(int)(game->player.pos_x - game->player.dir_x
				* game->move_speed)][(int)game->player.pos_y] != '1')
			game->player.pos_x -= game->player.dir_x * game->move_speed;
		if (game->resources.map[(int)game->player.pos_x][(int)(game->player.pos_y - game->player.dir_y
				* game->move_speed)] != '1')
			game->player.pos_y -= game->player.dir_y * game->move_speed;
	}
}

void	key_a_d(int keycode, t_game *game)
{
	if (keycode == KEY_A)
	{
		if (game->resources.map[(int)(game->player.pos_x - game->player.plane_x
				* game->move_speed)][(int)game->player.pos_y] == '0')
			game->player.pos_x -= game->player.plane_x * game->move_speed;
		if (game->resources.map[(int)game->player.pos_x][(int)(game->player.pos_y - game->player.plane_y
				* game->move_speed)] == '0')
			game->player.pos_y -= game->player.plane_y * game->move_speed;
	}
	if (keycode == KEY_D)
	{
		if (game->resources.map[(int)(game->player.pos_x + game->player.plane_x
				* game->move_speed)][(int)game->player.pos_y] == '0')
			game->player.pos_x += game->player.plane_x * game->move_speed;
		if (game->resources.map[(int)game->player.pos_x][(int)(game->player.pos_y + game->player.plane_y
				* game->move_speed)] == '0')
			game->player.pos_y += game->player.plane_y * game->move_speed;
	}
}

void	rotate(t_game *game, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	old_plane_x = game->player.plane_x;
	game->player.dir_x = old_dir_x * cos(angle)
		- game->player.dir_y * sin(angle);
	game->player.dir_y = old_dir_x * sin(angle)
		+ game->player.dir_y * cos(angle);
	game->player.plane_x = old_plane_x * cos(angle)
		- game->player.plane_y * sin(angle);
	game->player.plane_y = old_plane_x * sin(angle)
		+ game->player.plane_y * cos(angle);
}

int	key_handlers(int keycode, t_game *game)
{
	if (keycode == KEY_W || keycode == KEY_S)
		key_w_s(keycode, game);
	if (keycode == KEY_A || keycode == KEY_D)
		key_a_d(keycode, game);
	if (keycode == KEY_RIGHT_ARROW)
		rotate(game, game->rotate_speed);
	if (keycode == KEY_LEFT_ARROW)
		rotate(game, -game->rotate_speed);
	calculate(game);
	return (0);
}

int	close_window(t_game *game)
{
	(void)game;
	clean_resources(&game->resources);
	exit(EXIT_SUCCESS);
}

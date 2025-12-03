/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalkhidi <yalkhidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 18:48:52 by yalkhidi          #+#    #+#             */
/*   Updated: 2025/12/03 18:59:47 by yalkhidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    key_w(int keycode, t_game *game)
{
    if (keycode = KEY_W)
    {
        if (game->resources.map[(int)(game->player.pos_x + game->player.dir_x * game->move_speed)][(int)game->player.pos_y] == 0)
            game->player.pos_x += game->player.dir_x * game->move_speed;
        if (game->resources.map[(int)game->player.pos_x][(int)(game->player.pos_y + game->player.dir_y * game->move_speed)] == 0)
            game->player.pos_y += game->player.dir_y * game->move_speed;
    }
}
void    key_s(int keycode, t_game *game)
{
    if (keycode = KEY_W)
    {
        if (game->resources.map[(int)(game->player.pos_x - game->player.dir_x * game->move_speed)][(int)game->player.pos_y] == 0)
            game->player.pos_x -= game->player.dir_x * game->move_speed;
        if (game->resources.map[(int)game->player.pos_x][(int)(game->player.pos_y - game->player.dir_y * game->move_speed)] == 0)
            game->player.pos_y -= game->player.dir_y * game->move_speed;
    }
}
void    key_a(int keycode, t_game *game);
void    key_d(int keycode, t_game *game);
void    key_right(int keycode, t_game *game)
{
    
}
void    key_left(int keycode, t_game *game);
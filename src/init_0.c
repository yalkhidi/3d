/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalkhidi <yalkhidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 19:38:24 by omaimaqaroo       #+#    #+#             */
/*   Updated: 2025/12/04 17:04:31 by yalkhidi         ###   ########.fr       */
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
				game->player.pos_x = i + 0.5;
				game->player.pos_y = j + 0.5;
				game->player.facing_dir = l;
				return ;
			}
		}
	}
}

void	init_player_orientation(t_game *game)
{
	if (game->player.facing_dir == 'N')
	{
		game->player.dir_x = 0;
		game->player.dir_y = -1;
		game->player.plane_x = 0.66;
		game->player.plane_y = 0;
	}
	if (game->player.facing_dir == 'S')
	{
		game->player.dir_x = 0;
		game->player.dir_y = 1;
		game->player.plane_x = -0.66;
		game->player.plane_y = 0;
	}
	if (game->player.facing_dir == 'E')
	{
		game->player.dir_x = 1;
		game->player.dir_y = 0;
		game->player.plane_x = 0;
		game->player.plane_y = 0.66;
	}
	if (game->player.facing_dir == 'W')
	{
		game->player.dir_x = -1;
		game->player.dir_y = 0;
		game->player.plane_x = 0;
		game->player.plane_y = -0.66;
	}
}

void	init_textures(t_game *game)
{
	int		i;

	i = 0;
	while (i < 4)
	{
		game->textures[i].img = mlx_xpm_file_to_image(game->screen.mlx,
				game->resources.tex_path[i],
				&game->textures[i].width,
				&game->textures[i].height);
		if (!game->textures[i].img)
			exit_game("Error loading texture image", game);
		game->textures[i].buf = mlx_get_data_addr(game->textures[i].img,
				&game->textures[i].pix_bits,
				&game->textures[i].l_bytes,
				&game->textures[i].endian);
		if (!game->textures[i].buf)
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
	draw_background(game);
	game->time = get_time();
	game->old_time = game->time;
	game->move_speed = 0.0;
	game->rotate_speed = 0.0;
}

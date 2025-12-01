/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalkhidi <yalkhidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 19:38:24 by omaimaqaroo       #+#    #+#             */
/*   Updated: 2025/12/01 18:41:20 by yalkhidi         ###   ########.fr       */
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
				return ;
			}
		}
	}
}

void	init_player_orientation(t_game *game)
{
	char	c;

	c = game->resources.map[(int)game->player.pos_x][(int)game->player.pos_y];
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
}

void	calculate(t_game *game)
{
	int	x;
	double	camera_x;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		camera_x = 2.0 * x / (double)SCREEN_WIDTH - 1;
		game->ray.ray_dir_x = game->player.dir_x + game->player.plane_x
			* camera_x;
		game->ray.ray_dir_y = game->player.dir_y + game->player.plane_y
			* camera_x;
		
		game->ray.map_x = (int)game->player.pos_x;
		game->ray.map_y = (int)game->player.pos_y;
	
		game->ray.delta_dist_x = favs(1/ game->ray.ray_dir_x);
		game->ray.delta_dist_y = favs(1/ game->ray.ray_dir_y);

		
		x++;
	}
}

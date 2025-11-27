/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalkhidi <yalkhidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 19:38:24 by omaimaqaroo       #+#    #+#             */
/*   Updated: 2025/11/27 17:34:08 by yalkhidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_player_position(t_data *data)
{
	int	i;
	int	j;
	int	l;

	i = 0;
	while (++i < data->resources->map_height - 1)
	{
		j = 0;
		while (++j < data->resources->map_width - 1)
		{
			l = data->resources->map[i][j];
			if (l == 'N' || l == 'E' || l == 'S' || l == 'W')
			{
				data->pos_x = i + 0.5;
				data->pos_y = j + 0.5;
				return ;
			}
		}
	}
}

static void	init_player_orientation(t_data *data)
{
	char	c;

	c = data->resources->map[(int)data->pos_x][(int)data->pos_y];
	if (c == 'E')
	{
		data->dir_x = 0.0;
		data->dir_y = 1.0;
		data->plane_x = 0.66;
		data->plane_y = 0.0;
	}
	else if (c == 'S')
	{
		data->dir_x = 1.0;
		data->dir_y = 0.0;
		data->plane_x = 0.0;
		data->plane_y = -0.66;
	}
	else if (c == 'W')
	{
		data->dir_x = 0.0;
		data->dir_y = -1.0;
		data->plane_x = -0.66;
		data->plane_y = 0.0;
	}
}

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

void	init_ceiling_and_floor(t_data *data, t_resources *resources)
{
	data->ceiling_color = get_hex_from_rgb(resources->ceil_rgb[0],
			resources->ceil_rgb[1], resources->ceil_rgb[2]);
	data->floor_color = get_hex_from_rgb(resources->floor_rgb[0],
			resources->floor_rgb[1], resources->floor_rgb[2]);
}

void	init(t_data *data, t_resources *resources)
{
	data->resources = resources;
	data->mlx = mlx_init();
	if (data->mlx == NULL)
		error_msg("ERROR: data->mlx is NULL\n", data);
	data->win = mlx_new_window(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "CUB3D");
	if (data->win == NULL)
		error_msg("ERROR: data->win is NULL\n", data);
	data->img = NULL;
	init_player_position(data);
	data->dir_x = -1.0;
	data->dir_y = 0.0;
	data->plane_x = 0.0;
	data->plane_y = 0.66;
	if (data->resources->map[(int)data->pos_x][(int)data->pos_y] != 'N')
		init_player_orientation(data);
	init_ceiling_and_floor(data, resources);
	data->time = get_time(data);
	data->old_time = 0.0;
	data->view_shift = 0;
	data->texture = init_texture(data, resources);
}

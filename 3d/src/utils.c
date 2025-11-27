/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalkhidi <yalkhidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 19:40:01 by omaimaqaroo       #+#    #+#             */
/*   Updated: 2025/11/27 17:47:25 by yalkhidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	run_dda(t_data *data)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (data->side_dist_x < data->side_dist_y)
		{
			data->side_dist_x += data->delta_dist_x;
			data->map_x += data->step_x;
			data->side = 0;
		}
		else
		{
			data->side_dist_y += data->delta_dist_y;
			data->map_y += data->step_y;
			data->side = 1;
		}
		if (data->resources->map[data->map_x][data->map_y] == 49)
			hit = 1;
	}
}

long int	get_time(t_data *data)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		error_msg("gettimeofday() failed in get_time()\n", data);
	return ((tv.tv_sec * (long int)1000) + (tv.tv_usec / 1000));
}

// void	rotate_right(t_data *data, double rad)
// {
// 	double	old_dir;
// 	double	old_plane_x;

// 	old_dir = data->dir_x;
// 	data->dir_x = data->dir_x * cos(-rad) - data->dir_y * sin(-rad);
// 	data->dir_y = old_dir * sin(-rad) + data->dir_y * cos(-rad);
// 	old_plane_x = data->plane_x;
// 	data->plane_x = data->plane_x * cos(-rad) - data->plane_y * sin(-rad);
// 	data->plane_y = old_plane_x * sin(-rad) + data->plane_y * cos(-rad);
// }

// void	rotate_left(t_data *data, double rad)
// {
// 	double	old_dir;
// 	double	old_plane_x;

// 	old_dir = data->dir_x;
// 	data->dir_x = data->dir_x * cos(rad) - data->dir_y * sin(rad);
// 	data->dir_y = old_dir * sin(rad) + data->dir_y * cos(rad);
// 	old_plane_x = data->plane_x;
// 	data->plane_x = data->plane_x * cos(rad) - data->plane_y * sin(rad);
// 	data->plane_y = old_plane_x * sin(rad) + data->plane_y * cos(rad);
// }

void	rotate(t_data *data, double rad, char *rotate_side)
{
	double	old_dir;
	double	old_plane_x;

	old_dir = data->dir_x;
	old_plane_x = data->plane_x;
	if (!ft_strcmp(rotate_side, "left"))
	{
		data->dir_x = data->dir_x * cos(rad) - data->dir_y * sin(rad);
		data->dir_y = old_dir * sin(rad) + data->dir_y * cos(rad);
		data->plane_x = data->plane_x * cos(rad) - data->plane_y * sin(rad);
		data->plane_y = old_plane_x * sin(rad) + data->plane_y * cos(rad);
	}
	else if (!ft_strcmp(rotate_side, "right"))
	{
		data->dir_x = data->dir_x * cos(-rad) - data->dir_y * sin(-rad);
		data->dir_y = old_dir * sin(-rad) + data->dir_y * cos(-rad);
		data->plane_x = data->plane_x * cos(-rad) - data->plane_y * sin(-rad);
		data->plane_y = old_plane_x * sin(-rad) + data->plane_y * cos(-rad);
	}
}

uint32_t	get_hex_from_rgb(unsigned char r, unsigned char g, unsigned char b)
{
	return ((r << 16) | (g << 8) | b);
}

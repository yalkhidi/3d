/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalkhidi <yalkhidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 19:38:12 by omaimaqaroo       #+#    #+#             */
/*   Updated: 2025/11/27 17:51:05 by yalkhidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	w_s_keys(int key, t_data *data)
{
	if (key == KEY_W)
	{
		if (data->resources->map[(int)(data->pos_x + data->dir_x
				* data->move_speed)][(int)data->pos_y] != '1')
			data->pos_x += data->dir_x * data->move_speed;
		if (data->resources->map[(int)data->pos_x]
			[(int)(data->pos_y + data->dir_y * data->move_speed)] != '1')
			data->pos_y += data->dir_y * data->move_speed;
	}
	if (key == KEY_S)
	{
		if (data->resources->map[(int)(data->pos_x - data->dir_x
				* data->move_speed)][(int)data->pos_y] != '1')
			data->pos_x -= data->dir_x * data->move_speed;
		if (data->resources->map[(int)data->pos_x]
			[(int)(data->pos_y - data->dir_y * data->move_speed)] != '1')
			data->pos_y -= data->dir_y * data->move_speed;
	}
}

static void	a_d_keys(int key, t_data *data)
{
	if (key == KEY_D)
	{
		if (data->resources->map[(int)(data->pos_x + data->plane_x
				* data->move_speed)][(int)data->pos_y] != '1')
			data->pos_x += data->plane_x * data->move_speed;
		if (data->resources->map[(int)data->pos_x]
			[(int)(data->pos_y + data->plane_y * data->move_speed)] != '1')
			data->pos_y += data->plane_y * data->move_speed;
	}
	if (key == KEY_A)
	{
		if (data->resources->map[(int)(data->pos_x - data->plane_x
				* data->move_speed)][(int)data->pos_y] != '1')
			data->pos_x -= data->plane_x * data->move_speed;
		if (data->resources->map[(int)data->pos_x]
			[(int)(data->pos_y - data->plane_y * data->move_speed)] != '1')
			data->pos_y -= data->plane_y * data->move_speed;
	}
}

int	close_window(t_data *data)
{
	free_all(data);
	exit(0);
	return (0);
}

int	key_handler(int key, t_data *data)
{
	printf("keycode: %d\n", key);
	if (key != ESC)
	{
		if (key == KEY_W || key == KEY_S)
			w_s_keys(key, data);
		if (key == KEY_A || key == KEY_D)
			a_d_keys(key, data);
		if (key == KEY_LEFT_ARROW)
			rotate(data, data->rot_speed, "left");
		if (key == KEY_RIGHT_ARROW)
			rotate(data, data->rot_speed, "right");
		render(data);
	}
	if (key == ESC)
		close_window(data);
	return (0);
}

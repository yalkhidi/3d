/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalkhidi <yalkhidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 19:39:50 by omaimaqaroo       #+#    #+#             */
/*   Updated: 2025/11/27 17:38:45 by yalkhidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_move_rot_speeds(t_data *data)
{
	data->old_time = data->time;
	data->time = get_time(data);
	data->frame_time = (data->time - data->old_time) / 1000.0;
	data->move_speed = data->frame_time * 50.0;
	data->rot_speed = data->frame_time * 12.0;
}

void	plot(int x, int y, t_data *data, int color)
{
	int	pix;

	pix = (y * data->l_bytes) + (x * 4);
	if (x >= 0 && x * 4 < data->l_bytes && y >= 0 && pix < data->buf_size)
	{
		if (data->endi == 1)
		{
			data->buf[pix + 0] = (color >> 24);
			data->buf[pix + 1] = (color >> 16) & 0xFF;
			data->buf[pix + 2] = (color >> 8) & 0xFF;
			data->buf[pix + 3] = (color) & 0xFF;
		}
		else
		{
			data->buf[pix + 0] = (color) & 0xFF;
			data->buf[pix + 1] = (color >> 8) & 0xFF;
			data->buf[pix + 2] = (color >> 16) & 0xFF;
			data->buf[pix + 3] = (color >> 24);
		}
	}
}

void	draw_floor_and_ceiling(t_data *data)
{
	int	x;
	int	y;
	int	end;

	x = -1;
	y = -1;
	end = data->buf_size / 2;
	while (++x < SCREEN_WIDTH)
	{
		while (++y < SCREEN_HEIGHT / 2)
			plot(x, y, data, data->ceiling_color);
		while (++y < SCREEN_HEIGHT)
			plot(x, y, data, data->floor_color);
		y = 0;
	}
}

static void	calc_start_end(t_data *data)
{
	if (data->side == 0)
		data->perp_wall_dist = data->side_dist_x - data->delta_dist_x;
	else
		data->perp_wall_dist = data->side_dist_y - data->delta_dist_y;
	data->line_height = (int)(SCREEN_HEIGHT / data->perp_wall_dist);
	data->draw_start = -data->line_height / 2 + SCREEN_HEIGHT / 2
		+ data->view_shift;
	if (data->draw_start < 0)
		data->draw_start = 0;
	data->draw_end = data->line_height / 2 + SCREEN_HEIGHT / 2
		+ data->view_shift;
	if (data->draw_end >= SCREEN_HEIGHT)
		data->draw_end = SCREEN_HEIGHT - 1;
}

void	render(t_data *data)
{
	int	x;

	if (!data->img)
	{
		data->img = mlx_new_image(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
		data->buf = mlx_get_data_addr(data->img, &data->pix_bits,
				&data->l_bytes, &data->endi);
		data->buf_size = SCREEN_HEIGHT * data->l_bytes;
	}
	draw_floor_and_ceiling(data);
	x = -1;
	data->time = get_time(data);
	while (++x < SCREEN_WIDTH)
	{
		update_vars(x, data);
		run_dda(data);
		calc_start_end(data);
		draw_strip(data, x);
	}
	get_move_rot_speeds(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

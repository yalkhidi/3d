/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalkhidi <yalkhidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 19:37:24 by omaimaqaroo       #+#    #+#             */
/*   Updated: 2025/11/27 17:37:58 by yalkhidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	update_vars_(t_data *data)
{
	if (data->ray_dir_x < 0)
	{
		data->step_x = -1;
		data->side_dist_x = (data->pos_x - data->map_x) * data->delta_dist_x;
	}
	else
	{
		data->step_x = 1;
		data->side_dist_x = (data->map_x + 1.0 - data->pos_x)
			* data->delta_dist_x;
	}
	if (data->ray_dir_y < 0)
	{
		data->step_y = -1;
		data->side_dist_y = (data->pos_y - data->map_y)
			* data->delta_dist_y;
	}
	else
	{
		data->step_y = 1;
		data->side_dist_y = (data->map_y + 1.0 - data->pos_y)
			* data->delta_dist_y;
	}
}

void	update_vars(int x, t_data *data)
{
	data->camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
	data->ray_dir_x = data->dir_x + data->plane_x * data->camera_x;
	data->ray_dir_y = data->dir_y + data->plane_y * data->camera_x;
	data->map_x = (int)data->pos_x;
	data->map_y = (int)data->pos_y;
	if (data->ray_dir_x == 0)
		data->delta_dist_x = 1e30;
	else
		data->delta_dist_x = fabs(1 / data->ray_dir_x);
	if (data->ray_dir_y == 0)
		data->delta_dist_y = 1e30;
	else
		data->delta_dist_y = fabs(1 / data->ray_dir_y);
	update_vars_(data);
}

static unsigned char	get_texture_index(t_data *data)
{
	unsigned char	i;

	i = 0;
	if (data->side == 0 && data->pos_x < data->map_x)
		i = 2;
	else if (data->side == 0 && data->pos_x > data->map_x)
		i = 0;
	else if (data->side == 1 && data->pos_y > data->map_y)
		i = 3;
	else if (data->side == 1 && data->pos_y < data->map_y)
		i = 1;
	return (i);
}

static void	fill_strip_buffer(t_data *data, int x)
{
	unsigned char	i;
	int				y;
	int				tex_y;
	double			tex_pos;
	int				pix;

	y = data->draw_start - 1;
	data->step = 1.0 * (int)TEX_HEIGHT / data->line_height;
	tex_pos = (data->draw_start - data->view_shift - SCREEN_HEIGHT / 2
			+ data->line_height / 2) * data->step;
	i = get_texture_index(data);
	while (++y < data->draw_end)
	{
		tex_y = (int)tex_pos & (TEX_HEIGHT - 1);
		tex_pos += data->step;
		pix = y * data->l_bytes + x * 4;
		data->buf[pix + 0] = data->texture[i]->buf[data->texture[i]->l_bytes
			* tex_y + data->tex_x * 4];
		data->buf[pix + 1] = data->texture[i]->buf[data->texture[i]->l_bytes
			* tex_y + data->tex_x * 4 + 1];
		data->buf[pix + 2] = data->texture[i]->buf[data->texture[i]->l_bytes
			* tex_y + data->tex_x * 4 + 2];
		data->buf[pix + 3] = data->texture[i]->buf[data->texture[i]->l_bytes
			* tex_y + data->tex_x * 4 + 3];
	}
}

void	draw_strip(t_data *data, int x)
{
	data->tex_num = data->resources->map[data->map_x][data->map_y] - 1;
	if (data->side == 0)
		data->wall_x = data->pos_y + data->perp_wall_dist * data->ray_dir_y;
	else
		data->wall_x = data->pos_x + data->perp_wall_dist * data->ray_dir_x;
	data->wall_x -= floor(data->wall_x);
	data->tex_x = (int)(data->wall_x * (double)TEX_WIDTH);
	if (data->side == 0 && data->ray_dir_x > 0)
		data->tex_x = (int)TEX_WIDTH - data->tex_x - 1;
	if (data->side == 1 && data->ray_dir_y < 0)
		data->tex_x = (int)TEX_WIDTH - data->tex_x - 1;
	fill_strip_buffer(data, x);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalkhidi <yalkhidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 19:38:34 by omaimaqaroo       #+#    #+#             */
/*   Updated: 2025/11/27 17:44:11 by yalkhidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_texture	**init_texture(t_data *data, t_resources *resources)
{
	t_texture	**tex;
	int			i;

	tex = (t_texture **)malloc(sizeof(t_texture *) * 4);
	i = -1;
	while (++i < 4)
		tex[i] = (t_texture *)malloc(sizeof(t_texture));
	i = -1;
	while (++i < 4)
	{
		tex[i]->path = resources->tex_path[i];
		tex[i]->img = mlx_xpm_file_to_image(data->mlx, tex[i]->path,
				&tex[i]->width, &tex[i]->height);
		if (tex[i]->img == NULL)
			error_msg("ERROR: tex[i]->img is NULL", data);
		tex[i]->buf = mlx_get_data_addr(tex[i]->img, &tex[i]->pix_bits,
				&tex[i]->l_bytes, &tex[i]->endi);
	}
	return (tex);
}

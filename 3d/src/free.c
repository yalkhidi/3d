/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalkhidi <yalkhidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 19:37:44 by omaimaqaroo       #+#    #+#             */
/*   Updated: 2025/11/27 16:41:43 by yalkhidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clean_resources(t_resources *resources)
{
	t_row_list	*tmp;
	t_row_list	*tmp2;
	int			i;

	free(resources->tex_path[0]);
	free(resources->tex_path[1]);
	free(resources->tex_path[2]);
	free(resources->tex_path[3]);
	tmp = resources->rowlist;
	while (tmp)
	{
		tmp2 = tmp->next;
		if (tmp->row)
			free(tmp->row);
		if (tmp)
			free(tmp);
		tmp = tmp2;
	}
	i = -1;
	while (resources->map && ++i < resources->map_height)
		if (resources->map[i])
			free(resources->map[i]);
	if (resources->map)
		free(resources->map);
}

static void	clean_textures(t_data *data)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		mlx_destroy_image(data->mlx, data->texture[i]->img);
		free(data->texture[i]);
	}
	free(data->texture);
}

void	error_msg(char *str, t_data *data)
{
	printf("%s\n", str);
	if (data)
		free_all(data);
	exit(0);
}

void	free_all(t_data *data)
{
	clean_resources(data->resources);
	clean_textures(data);
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_window(data->mlx, data->win);
	return ;
}

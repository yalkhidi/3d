/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalkhidi <yalkhidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 19:37:44 by omaimaqaroo       #+#    #+#             */
/*   Updated: 2025/12/04 09:54:42 by yalkhidi         ###   ########.fr       */
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
	free(resources->tex_path);
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

void	exit_game(char *msg, t_game *game)
{
	if (msg)
		ft_putendl_fd(msg, 2);
	clean_resources(&game->resources);
	exit(0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalkhidi <yalkhidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 19:39:12 by omaimaqaroo       #+#    #+#             */
/*   Updated: 2025/12/01 12:10:50 by yalkhidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_open(t_resources *resources, int row, int col)
{
	if (row >= resources->map_height || row < 0 || col >= resources->map_width
		|| col < 0)
		return (1);
	if (resources->map[row][col] == ' ')
		return (1);
	return (0);
}

int	check_map(t_resources *resources)
{
	int	i;
	int	j;

	if (additional_check(resources) < 1)
		return (0);
	i = -1;
	while (++i < resources->map_height)
	{
		j = -1;
		while (++j < resources->map_width)
		{
			if (resources->map[i][j] != ' ' && resources->map[i][j] != '1')
			{
				if (is_open(resources, i - 1, j) || is_open(resources, i, j + 1)
					|| is_open(resources, i + 1, j)
					|| is_open(resources, i, j - 1))
				{
					write(STDERR_FILENO, "Error\nMap not enclosed\n", 23);
					return (0);
				}
			}
		}
	}
	return (1);
}

int	add_rownode(t_resources *resources, t_row_list *node)
{
	t_row_list	*tmp;

	if (resources->rowlist == NULL)
		resources->rowlist = node;
	else
	{
		tmp = resources->rowlist;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}
	return (1);
}

static int	init_map(t_resources *resources)
{
	int	i;

	resources->map = (int **)malloc(sizeof(int *)
			* (resources->map_height + 1));
	if (!resources->map)
		return (-2 - write(STDERR_FILENO, "Error\n", 6));
	i = 0;
	while (i <= resources->map_height)
	{
		resources->map[i] = NULL;
		i++;
	}
	i = 0;
	while (i < resources->map_height)
	{
		resources->map[i] = (int *)malloc(sizeof(int) * (resources->map_width));
		if (!resources->map)
		{
			write(STDERR_FILENO, "Error\n", 6);
			return (-1);
		}
		i++;
	}
	return (1);
}

int	list_to_matrix(t_resources *resources)
{
	int			i;
	int			j;
	t_row_list	*tmp;

	if (init_map(resources) <= 0)
		return (-1);
	i = 0;
	tmp = resources->rowlist;
	while (i < resources->map_height)
	{
		j = 0;
		while (j < resources->map_width)
		{
			if (j < tmp->size)
				resources->map[i][j] = tmp->row[j];
			else
				resources->map[i][j] = ' ';
			j++;
		}
		tmp = tmp->next;
		i++;
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalkhidi <yalkhidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 19:39:23 by omaimaqaroo       #+#    #+#             */
/*   Updated: 2025/11/27 16:36:55 by yalkhidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	additional_check(t_resources *resources)
{
	if (resources->map_height == 0)
	{
		write(STDERR_FILENO, "Error\nNo map\n", 13);
		return (0);
	}
	if (check_char(0, 1) != 1)
	{
		write(STDERR_FILENO, "Error\nNo player\n", 16);
		return (0);
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalkhidi <yalkhidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 19:38:42 by omaimaqaroo       #+#    #+#             */
/*   Updated: 2025/11/27 17:43:37 by yalkhidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	print_resources(t_resources *resources)
{
	int	i;
	int	j;

	printf("North Texture	\"%s\"\n", resources->tex_path[0]);
	printf("South Texture	\"%s\"\n", resources->tex_path[2]);
	printf("West Texture	\"%s\"\n", resources->tex_path[3]);
	printf("East Texture	\"%s\"\n", resources->tex_path[1]);
	printf("Floor %i,%i,%i\n", resources->floor_rgb[0], resources->floor_rgb[1],
		resources->floor_rgb[2]);
	printf("Ceiling %i,%i,%i\n", resources->ceil_rgb[0], resources->ceil_rgb[1],
		resources->ceil_rgb[2]);
	printf("MAP:\n");
	i = 0;
	while (i < resources->map_height)
	{
		j = 0;
		while (j < resources->map_width)
		{
			printf("%c", resources->map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_data		data;
	t_resources	resources;

	errno = 0;
	init_resources(&resources);
	if (parse(argc, argv, &resources) <= 0)
		return (EXIT_FAILURE);
	print_resources(&resources);
	init(&data, &resources);
	render(&data);
	mlx_hook(data.win, 2, 0, key_handler, &data);
	mlx_hook(data.win, 17, 0, close_window, &data);
	mlx_loop(data.mlx);
	return (EXIT_SUCCESS);
}

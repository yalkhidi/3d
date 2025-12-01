/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalkhidi <yalkhidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 19:38:42 by omaimaqaroo       #+#    #+#             */
/*   Updated: 2025/12/01 18:20:32 by yalkhidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_content(t_resources *c)    // static means we are using this function only here , and it's only used by the int main
{
	int	i;
	int	j;

	printf("North Texture	\"%s\"\n", c->tex_path[0]);
	printf("South Texture	\"%s\"\n", c->tex_path[2]);
	printf("West Texture	\"%s\"\n", c->tex_path[3]);
	printf("East Texture	\"%s\"\n", c->tex_path[1]);
	printf("Floor %i,%i,%i\n", c->floor_rgb[0], c->floor_rgb[1],
		c->floor_rgb[2]);
	printf("Ceiling %i,%i,%i\n", c->ceil_rgb[0], c->ceil_rgb[1],
		c->ceil_rgb[2]);
	printf("map width: %d\n", c->map_width);
	printf("map height: %d\n", c->map_height);
	printf("MAP:\n");
	i = 0;
	while (i < c->map_height)
	{
		j = 0;
		while (j < c->map_width)
		{
			printf("%c", c->map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

int	main(int argc, char *argv[])
{
	// t_resources	resources;
	t_game game;

	errno = 0;
	init_resources(&game.resources);
	if (parse(argc, argv, &game.resources) <= 0)
		return (EXIT_FAILURE);
	print_content(&game.resources);
	init_game(&game);
	mlx_loop(game.screen.mlx);
	// clean_resources(&game.resources);
}

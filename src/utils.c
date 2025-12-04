/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalkhidi <yalkhidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 15:06:30 by yalkhidi          #+#    #+#             */
/*   Updated: 2025/12/04 17:57:47 by yalkhidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
		return ;
	dst = game->screen.buf
		+ (y * game->screen.l_bytes + x * (game->screen.pix_bits / 8));
	*(unsigned int *)dst = color;
}

long int	get_time(void)
{
	struct timeval	tv;		

	if (gettimeofday(&tv, NULL) == -1)
	{
		perror("gettimeofday failed");
		return (0);
	}
	return ((tv.tv_sec * (long int)1000) + (tv.tv_usec / 1000));
}

uint32_t	get_hex_from_rgb(unsigned char r, unsigned char g, unsigned char b)
{
	return ((r << 16) | (g << 8) | b);
}

int	get_tex_color(t_game *game, int tex_id, int tex_x, int tex_y)
{
	char	*tex_addr;
	int		color;
	int		line_len;
	int		bpp;

	tex_addr = game->textures[tex_id].buf;
	line_len = game->textures[tex_id].l_bytes;
	bpp = game->textures[tex_id].pix_bits;
	color = *(unsigned int *)(tex_addr
			+ (tex_y * line_len + tex_x * (bpp / 8)));
	return (color);
}

void	draw_background(t_game *game)
{
	int	ceiling;
	int	floor;
	int	x;
	int	y;

	ceiling = get_hex_from_rgb(game->resources.ceil_rgb[0],
			game->resources.ceil_rgb[1], game->resources.ceil_rgb[2]);
	floor = get_hex_from_rgb(game->resources.floor_rgb[0],
			game->resources.floor_rgb[1], game->resources.floor_rgb[2]);
	printf("Ceiling color set to 0x%06X\n", ceiling);
	x = 0;
	while (x < SCREEN_WIDTH)
	{
		y = 0;
		while (y < SCREEN_HEIGHT / 2)
		{
			put_pixel(game, x, y, ceiling);
			y++;
		}
		while (y < SCREEN_HEIGHT)
		{
			put_pixel(game, x, y, floor);
			y++;
		}
		x++;
	}
	// mlx_put_image_to_window(game->screen.mlx, game->screen.win,
	// 	game->screen.img, 0, 0);
}

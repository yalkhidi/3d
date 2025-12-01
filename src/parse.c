/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalkhidi <yalkhidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 19:39:34 by omaimaqaroo       #+#    #+#             */
/*   Updated: 2025/12/01 13:17:58 by yalkhidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	free_gnl(char *line, int fd, int ret_val)
{
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	return (ret_val);
}

int clean_and_print_error(char *msg, t_resources *resources, int ret_val)
{
	if (resources)
		clean_resources(resources);
	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	return (ret_val);
}

static int	check_warning(int argc, char *argv[], t_resources *resources)
{
	int	fd;
	int	i;

	if (argc != 2 || !argv || !argv[0] || !argv[1])
		return (clean_and_print_error("Number of arguments expected: 1\n", resources, -1));
	i = 0;
	while (argv[1][i])
		i++;
	if (ft_strcmp(argv[1] + i - 4, ".cub") != 0)
		return (clean_and_print_error("Extension expected: \".cub\"\n", resources, -1));
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (clean_and_print_error("No such file\n", resources, -1));
	return (fd);
}

static int	assign_texture(char **texture, char *str)
{
	int	i;

	if (*texture)
		return (1 - write(STDERR_FILENO, "Error\nElement duplicate\n", 24));
	*texture = ft_strdup(str);
	if (*texture == NULL)
	{
		write(STDERR_FILENO, "Error\n", 6);
		perror(NULL);
		return (-1);
	}
	i = 0;
	while ((*texture)[i] && (*texture)[i] != '\n')
		i++;
	(*texture)[i] = 0;
	i = open(*texture, O_RDONLY);
	if (i < 0 || read(i, str, 1) < 0)
	{
		if (i >= 0)
			close(i);
		return (1 - write(STDERR_FILENO, "Error\nWrong texture file\n", 25));
	}
	close(i);
	return (1);
}

static int	parse_line(char *str, t_resources *resources)
{
	static int	map_done;
	int			i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == 0 || str[i] == '\n')
	{
		if (map_done == 0 && resources->rowlist)
			map_done = 1;
		return (1);
	}
	if (ft_strncmp(str + i, "NO", 2) == 0 && ft_isspace(str[i + 2]))
		return (assign_texture(&resources->tex_path[0], str + i + 3));
	if (ft_strncmp(str + i, "SO", 2) == 0 && ft_isspace(str[i + 2]))
		return (assign_texture(&resources->tex_path[2], str + i + 3));
	if (ft_strncmp(str + i, "WE", 2) == 0 && ft_isspace(str[i + 2]))
		return (assign_texture(&resources->tex_path[3], str + i + 3));
	if (ft_strncmp(str + i, "EA", 2) == 0 && ft_isspace(str[i + 2]))
		return (assign_texture(&resources->tex_path[1], str + i + 3));
	if (str[i] == 'F' && ft_isspace(str[i + 1]))
		return (assign_rgb(resources->floor_rgb, str + i + 2));
	if (str[i] == 'C' && ft_isspace(str[i + 1]))
		return (assign_rgb(resources->ceil_rgb, str + i + 2));
	// printf("str: %s\n", str);
	return (add_mapline(str, resources, map_done));
}

static int	parse_elements(int fd, t_resources *resources)
{
	char	*str;

	str = get_next_line(fd);
	while (str)
	{
		if (parse_line(str, resources) <= 0)
			return (free_gnl(str, fd, 0));
		free(str);
		str = get_next_line(fd);
	}
	if (errno != 0)
	{
		write(STDERR_FILENO, "Error\n", 6);
		perror(NULL);
		return (free_gnl(str, fd, -1));
	}
	if (list_to_matrix(resources) <= 0)
		return (free_gnl(str, fd, 0));
	if (check_map(resources) <= 0)
		return (free_gnl(str, fd, 0));
	return (free_gnl(str, fd, 1));
}

int	parse(int argc, char *argv[], t_resources *resources)
{
	int	fd;

	fd = check_warning(argc, argv, resources);
	if (fd < 0)
		return (0);
	if (parse_elements(fd, resources) <= 0)
	{
		close(fd);
		clean_resources(resources);
		return (0);
	}
	if (close(fd) < 0)
	{
		write(STDERR_FILENO, "Error\n", 6);
		perror(NULL);
		return (0);
	}
	return (1);
}

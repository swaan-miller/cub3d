/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_res.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: smiller <smiller@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/02 18:10:07 by smiller       #+#    #+#                 */
/*   Updated: 2021/10/23 22:13:03 by smiller       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		skip_spaces(char **line)
{
	while (**line == SPACE)
		(*line)++;
}

static void	get_res(t_cub *scene, char **line, unsigned long long res)
{
	if (res == scene->res_width)
		scene->res = &scene->res_width;
	else
		scene->res = &scene->res_height;
	skip_spaces(line);
	if (ft_isdigit(**line))
	{
		while (ft_isdigit(**line))
		{
			*scene->res = (*scene->res * 10) + (**line - '0');
			(*line)++;
		}
		if (**line == SPACE || **line == '\0')
			skip_spaces(line);
		else
			error("Unable to set resolution.");
	}
	else
		error("Invalid resolution.");
}

int			set_res(t_cub *scene, char **line)
{
	(*line)++;
	skip_spaces(line);
	get_res(scene, line, scene->res_width);
	get_res(scene, line, scene->res_height);
	if (**line == '\0' && scene->res_width != 0 && scene->res_height != 0)
	{
		scene->typeid.res = ON;
		scene->typeid.count++;
		return (SUCCESS);
	}
	return (error("Unable to set resolution."));
}

static int	get_info(t_cub *scene, char *line)
{
	if (ft_strncmp(scene->error, "\0\0\0", 3) != 0 && scene->ret == 0)
		check_elements(scene);
	if (scene->typeid.count == 8)
		return (check_map(scene, line));
	if (*line == '\0')
		return (SUCCESS);
	skip_spaces(&line);
	if (ft_strncmp(line, "R ", 2) == 0 && scene->typeid.res == OFF)
		return (set_res(scene, &line));
	if (ft_strncmp(line, "F ", 2) == 0 && scene->typeid.floor == OFF)
		return (set_floor_ceiling(scene, line));
	if (ft_strncmp(line, "C ", 2) == 0 && scene->typeid.ceiling == OFF)
		return (set_floor_ceiling(scene, line));
	if (ft_strncmp(line, "S ", 2) == 0 || ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0)
		return (set_path(scene, line));
	if (scene->typeid.count < 8)
	{
		ft_strlcpy(scene->error, line, 3);
		return (1);
	}
	return (error("Invalid cub file elements."));
}

void		parse_cub(t_cub *scene)
{
	scene->ret = 1;
	while (scene->ret != 0)
	{
		scene->ret = get_next_line(scene->fd, &scene->line);
		if (scene->ret == ERROR)
			error("Error reading line.");
		get_info(scene, scene->line);
		free(scene->line);
	}
	if (ft_strncmp(scene->error, "\0\0\0", 3) != 0)
		error("Invalid cub file.");
	if (scene->typeid.count == 0 && scene->array.buf == NULL)
		error("Empty file.");
	if (scene->typeid.count != 8)
		error("Invalid number of elements.");
	if (scene->array.buf == NULL)
		error("Missing map.");
}

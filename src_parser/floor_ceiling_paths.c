/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   floor_ceiling_paths.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: smiller <smiller@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/27 16:27:33 by smiller       #+#    #+#                 */
/*   Updated: 2021/10/23 22:13:06 by smiller       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	get_color(char **line, int *rgb, t_cub *scene)
{
	(*line)++;
	skip_spaces(line);
	if (ft_isdigit(**line))
	{
		while (ft_isdigit(**line))
		{
			*rgb = (*rgb * 10) + (**line - '0');
			(*line)++;
		}
		if (*rgb >= 0 && *rgb <= 255)
		{
			skip_spaces(line);
			return ;
		}
	}
	if (scene->ptr == &scene->floor)
		error("Invalid floor color.");
	error("Invalid ceiling color.");
}

int			set_floor_ceiling(t_cub *scene, char *line)
{
	if (ft_strncmp(line, "F ", 2) == 0)
		scene->ptr = &scene->floor;
	else
		scene->ptr = &scene->ceiling;
	get_color(&line, &scene->ptr->red, scene);
	if (*line == ',')
	{
		get_color(&line, &scene->ptr->green, scene);
		if (*line == ',')
		{
			get_color(&line, &scene->ptr->blue, scene);
			if (*line == '\0')
			{
				if (scene->ptr == &scene->floor)
					scene->typeid.floor = ON;
				else
					scene->typeid.ceiling = ON;
				scene->typeid.count++;
				return (SUCCESS);
			}
		}
	}
	return (error("Unable to set floor or ceiling color."));
}

static int	get_path(t_cub *scene, char *line, char **path)
{
	int		fd;

	scene->typeid.count++;
	line = line + 2;
	skip_spaces(&line);
	scene->path.len = ft_strlen(line);
	*path = ft_substr(line, 0, scene->path.len);
	if (*path == NULL)
		error("Memory allocation failed.");
	fd = open(*path, O_RDWR);
	if (fd == ERROR)
		error("Unable to open texture or sprite path.");
	close(fd);
	line = line + scene->path.len;
	skip_spaces(&line);
	if (*line == '\0')
		return (SUCCESS);
	return (error("Unable to set texture path."));
}

int			set_path(t_cub *scene, char *line)
{
	if (ft_strncmp(line, "S ", 2) == 0 && scene->path.sprt == NULL)
		return (get_path(scene, line, &scene->path.sprt));
	else if (ft_strncmp(line, "S ", 2) == 0 && scene->path.sprt != NULL)
		return (error("Duplicate sprite path."));
	else if (ft_strncmp(line, "NO", 2) == 0 && scene->path.nrth == NULL)
		return (get_path(scene, line, &scene->path.nrth));
	else if (ft_strncmp(line, "NO", 2) == 0 && scene->path.nrth != NULL)
		return (error("Duplicate north texture path."));
	else if (ft_strncmp(line, "SO", 2) == 0 && scene->path.south == NULL)
		return (get_path(scene, line, &scene->path.south));
	else if (ft_strncmp(line, "SO", 2) == 0 && scene->path.south != NULL)
		return (error("Duplicate south texture path."));
	else if (ft_strncmp(line, "EA", 2) == 0 && scene->path.east == NULL)
		return (get_path(scene, line, &scene->path.east));
	else if (ft_strncmp(line, "EA", 2) == 0 && scene->path.east != NULL)
		return (error("Duplicate east texture path."));
	else if (ft_strncmp(line, "WE", 2) == 0 && scene->path.wst == NULL)
		return (get_path(scene, line, &scene->path.wst));
	else if (ft_strncmp(line, "WE", 2) == 0 && scene->path.wst == NULL)
		return (error("Duplicate west texture path."));
	return (error("Duplicate texture path."));
}

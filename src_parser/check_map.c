/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: smiller <smiller@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/08 10:32:32 by smiller       #+#    #+#                 */
/*   Updated: 2021/10/23 22:13:14 by smiller       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	set_start(t_cub *scene, char *line)
{
	int		i;

	i = 0;
	while (line[i] && ft_strchr(" NSWE012", line[i]))
	{
		if (ft_strchr("NSWE", line[i]))
		{
			if (scene->array.start_dir == 0)
				scene->array.start_dir = line[i];
			else
				error("Duplicate start position.");
		}
		i++;
	}
}

/*
** once reading has been done allocates and fills array
*/

static int	array(t_cub *scene)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	allocate_array(scene, x, y);
	flood_fill(scene, scene->array.start_x, scene->array.start_y, FILL);
	x = 1;
	while (scene->array.line_count + 1 > x)
	{
		y = 1;
		while (y < scene->array.longest + 2)
		{
			check_flood_fill(scene, x, y);
			y++;
		}
		x++;
	}
	return (SUCCESS);
}

/*
** reads each line of map and concatenates into buf
** adding a comma at the end and null terminating
*/

static int	parse_map(t_cub *scene)
{
	int		i;

	i = 0;
	if (scene->array.longest * scene->array.line_count > 60000)
		error("Map is too large.");
	scene->array.tmp = ft_calloc(scene->array.len + 2, sizeof(scene->line));
	if (scene->array.tmp == NULL)
		error("Memory allocation failed.");
	ft_strlcpy(scene->array.tmp, scene->line, scene->array.len + 2);
	scene->array.tmp[scene->array.len] = ',';
	scene->array.tmp[scene->array.len + 1] = '\0';
	scene->array.str = ft_strjoin(scene->array.buf, scene->array.tmp);
	if (scene->array.str == NULL)
		error("Memory allocation failed.");
	free(scene->array.tmp);
	free(scene->array.buf);
	scene->array.buf = ft_strdup(scene->array.str);
	if (scene->array.buf == NULL)
		error("Memory allocation failed.");
	free(scene->array.str);
	if (scene->ret == 0)
		array(scene);
	return (SUCCESS);
}

static void	valid_chars(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (ft_strchr(" NSWE012", line[i]))
			i++;
		else
			error("Invalid characters in map.");
	}
}

int			check_map(t_cub *scene, char *line)
{
	skip_spaces(&line);
	if (*line == '\0' && scene->array.buf == NULL)
		return (SUCCESS);
	if (scene->ret == 0 && scene->array.start_dir == '\0')
		error("Start position missing.");
	if (*line == '\0' && scene->ret == 0)
		return (array(scene));
	if (*line != '\0' && scene->newline > 0)
		error("Newline in map.");
	if (*line == '\0')
	{
		scene->newline++;
		return (1);
	}
	valid_chars(line);
	set_start(scene, line);
	scene->array.line_count++;
	if (scene->array.buf == NULL)
		scene->array.buf = ft_strdup("");
	scene->array.len = ft_strlen(scene->line);
	if (scene->array.len > scene->array.longest)
		scene->array.longest = scene->array.len;
	return (parse_map(scene));
}

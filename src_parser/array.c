/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   array.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smiller <smiller@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/08 10:29:12 by smiller       #+#    #+#                 */
/*   Updated: 2021/10/23 22:13:18 by smiller       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		check_flood_fill(t_cub *scene, int x, int y)
{
	if (scene->map[x][y] == FILL)
	{
		if ((scene->map[x - 1][y] != '1' && scene->map[x - 1][y] != FILL)
		|| (scene->map[x][y + 1] != '1' && scene->map[x][y + 1] != FILL)
		|| (scene->map[x][y - 1] != '1' && scene->map[x][y - 1] != FILL)
		|| (scene->map[x + 1][y - 1] != '1' && scene->map[x + 1][y - 1] != FILL)
		|| (scene->map[x - 1][y + 1] != '1' && scene->map[x - 1][y + 1] != FILL)
		|| (scene->map[x + 1][y + 1] != '1' && scene->map[x + 1][y + 1] != FILL)
		|| (scene->map[x - 1][y - 1] != '1' && scene->map[x - 1][y - 1] != FILL)
		|| (scene->map[x + 1][y] != '1' && scene->map[x + 1][y] != FILL))
			error("Invalid map.");
	}
}

void		flood_fill(t_cub *scene, int x, int y, char color)
{
	if (scene->map[x][y] == WALL || scene->map[x][y] == color || x < 1 || y < 1
		|| x > scene->array.line_count || y > scene->array.longest)
		return ;
	if (scene->map[x][y] != '0' && scene->map[x][y] != scene->array.start_dir
		&& scene->map[x][y] != '2')
		return ;
	scene->map[x][y] = color;
	flood_fill(scene, x + 1, y, color);
	flood_fill(scene, x - 1, y, color);
	flood_fill(scene, x, y + 1, color);
	flood_fill(scene, x, y - 1, color);
	flood_fill(scene, x + 1, y + 1, color);
	flood_fill(scene, x - 1, y - 1, color);
	flood_fill(scene, x - 1, y + 1, color);
	flood_fill(scene, x + 1, y - 1, color);
	return ;
}

static int	fill(t_cub *scene, int i, int x, int y)
{
	scene->map[x][y] = ' ';
	y++;
	while (scene->array.buf[i] != ',')
	{
		if (scene->array.buf[i] == '2')
			scene->num_sprites++;
		scene->map[x][y] = scene->array.buf[i];
		if (scene->map[x][y] == scene->array.start_dir)
		{
			scene->array.start_x = x;
			scene->array.start_y = y;
		}
		i++;
		y++;
		if (scene->array.buf[i] == ',')
		{
			while (y <= scene->array.longest + 1)
			{
				scene->map[x][y] = ' ';
				y++;
			}
			scene->map[x][y] = '\0';
		}
	}
	return (i);
}

static void	add_spaces_row(t_cub *scene, int x, int y)
{
	scene->map[x] = ft_calloc(scene->array.longest + 3, sizeof(char));
	if (scene->map[x] == NULL)
		error("Memory allocation failed.");
	while (y <= scene->array.longest + 1)
	{
		scene->map[x][y] = ' ';
		y++;
	}
	scene->map[x][y] = '\0';
}

void		allocate_array(t_cub *scene, int x, int y)
{
	int		i;

	i = 0;
	scene->map = ft_calloc(scene->array.line_count + 2, sizeof(char*));
	if (scene->map == NULL)
		error("Memory allocation failed.");
	add_spaces_row(scene, x, y);
	x++;
	while (scene->array.line_count >= x && scene->array.buf[i])
	{
		y = 0;
		scene->map[x] = ft_calloc(scene->array.longest + 3, sizeof(char));
		if (scene->map[x] == NULL)
			error("Memory allocation failed.");
		if (scene->array.buf[i] != ',')
			i = fill(scene, i, x, y);
		x++;
		i++;
	}
	y = 0;
	add_spaces_row(scene, x, y);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_vars.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smiller <smiller@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/25 14:45:07 by smiller       #+#    #+#                 */
/*   Updated: 2021/10/23 22:12:50 by smiller       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	fill_map(t_vars *game, t_cub *scene)
{
	while (scene->array.buf[game->map_i] != ',')
	{
		if (scene->array.buf[game->map_i] == '2')
		{
			game->sprite[game->sprite->counter].x = game->map_x + .5;
			game->sprite[game->sprite->counter].y = game->map_y + .5;
			game->sprite->counter++;
		}
		game->map[game->map_x][game->map_y] = scene->array.buf[game->map_i];
		game->map_i++;
		game->map_y++;
	}
	game->map[game->map_x][game->map_y] = '\0';
}

void		set_map(t_vars *game, t_cub *scene)
{
	game->map = ft_calloc(scene->array.line_count, sizeof(char*));
	if (game->map == NULL)
		error("Map memory allocation failed.");
	while (scene->array.line_count > game->map_x)
	{
		game->map_y = 0;
		game->map[game->map_x] =
		ft_calloc(scene->array.longest + 1, sizeof(char));
		if (game->map[game->map_x] == NULL)
			error("Map memory allocation failed.");
		fill_map(game, scene);
		game->map_i++;
		game->map_x++;
	}
	game->map[scene->array.start_x - 1][scene->array.start_y - 1] = '0';
}

void		set_player_vars(t_vars *game, t_cub *scene)
{
	game->pos_x = scene->array.start_x - .5;
	game->pos_y = scene->array.start_y - .5;
	game->cardinal_dir = scene->array.start_dir;
	if (scene->array.start_dir == 'N')
		game->dir_x = -1;
	if (scene->array.start_dir == 'W')
		game->dir_y = -1;
	if (scene->array.start_dir == 'S')
		game->dir_x = 1;
	if (scene->array.start_dir == 'E')
		game->dir_y = 1;
	game->cameraplane_y = .66;
	if (game->dir_y != 0)
	{
		game->cameraplane_x = .66;
		game->cameraplane_y = 0;
	}
	if (game->cardinal_dir == 'S' || game->cardinal_dir == 'W')
		game->reverse_raydir = 1;
}

void		set_screen_vars(t_vars *game, t_cub *scene)
{
	if (game->screenshot == 1)
	{
		if (scene->res_width >= 16384)
			scene->res_width = 16384;
		if (scene->res_height >= 16384)
			scene->res_height = 16384;
	}
	if (game->screenshot == 0)
	{
		if (scene->res_width > (unsigned long long)game->screen_width)
			scene->res_width = game->screen_width;
		if (scene->res_height > (unsigned long long)game->screen_height)
			scene->res_height = game->screen_height;
	}
	game->screen_width = scene->res_width;
	game->screen_height = scene->res_height;
	game->floor = scene->floor.blue + (scene->floor.green * pow(16, 2))
				+ (scene->floor.red * pow(16, 4));
	game->ceiling = scene->ceiling.blue + (scene->ceiling.green * pow(16, 2))
				+ (scene->ceiling.red * pow(16, 4));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycast_scene.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: smiller <smiller@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/25 16:32:10 by smiller       #+#    #+#                 */
/*   Updated: 2021/10/23 22:12:31 by smiller       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
** raydir - ray coordinates on camera plane from player position
** revers_raydir - if S or W need to reverse raydirx and raydiry
** otherwise image will be mirrored
** deltadist - length from one x side to another and one y side to another
*/

void	raydir_deltadist(t_vars *game)
{
	if (game->reverse_raydir == 1)
	{
		game->raydir_x = game->dir_x + game->cameraplane_x * -game->camera_x;
		game->raydir_y = game->dir_y + game->cameraplane_y * -game->camera_x;
	}
	else
	{
		game->raydir_x = game->dir_x + game->cameraplane_x * game->camera_x;
		game->raydir_y = game->dir_y + game->cameraplane_y * game->camera_x;
	}
	if (game->raydir_y == 0)
		game->deltadist_x = 0;
	else if (game->raydir_x == 0)
		game->deltadist_x = 1;
	else
		game->deltadist_x = fabs(1 / game->raydir_x);
	if (game->raydir_x == 0)
		game->deltadist_y = 0;
	else if (game->raydir_y == 0)
		game->deltadist_y = 1;
	else
		game->deltadist_y = fabs(1 / game->raydir_y);
}

/*
** set which box of the map the ray is in
** sidedist - initial length from player to first x and y side
** step - direction to move in the map to follow the ray
*/

void	sidedist(t_vars *game)
{
	game->mapray_x = (int)game->pos_x;
	game->mapray_y = (int)game->pos_y;
	if (game->raydir_x < 0)
	{
		game->step_x = -1;
		game->sidedist_x = (game->pos_x - game->mapray_x) * game->deltadist_x;
	}
	else
	{
		game->step_x = 1;
		game->sidedist_x = (game->mapray_x + 1.0 - game->pos_x) *
		game->deltadist_x;
	}
	if (game->raydir_y < 0)
	{
		game->step_y = -1;
		game->sidedist_y = (game->pos_y - game->mapray_y) * game->deltadist_y;
	}
	else
	{
		game->step_y = 1;
		game->sidedist_y = (game->mapray_y + 1.0 - game->pos_y) *
		game->deltadist_y;
	}
}

/*
** using step jump to next map square in x direction or in y direction
** if wall hit is x-side (vertical)then side = 0, y side then side = 1
** perpwalldist - distance from camera plane to wall
** need perpwalldist because Euclidean distance will give fisheye effect
*/

void	wall_hit(t_vars *game)
{
	game->hit = 0;
	while (game->hit == 0)
	{
		if (game->sidedist_x < game->sidedist_y)
		{
			game->sidedist_x = game->sidedist_x + game->deltadist_x;
			game->mapray_x = game->mapray_x + game->step_x;
			game->side = 0;
		}
		else
		{
			game->sidedist_y = game->sidedist_y + game->deltadist_y;
			game->mapray_y = game->mapray_y + game->step_y;
			game->side = 1;
		}
		if (game->map[game->mapray_x][game->mapray_y] == '1')
			game->hit = 1;
		if (game->side == 0)
			game->perpwalldist = (game->mapray_x - game->pos_x
			+ (1 - game->step_x) / 2) / game->raydir_x;
		else
			game->perpwalldist = (game->mapray_y - game->pos_y
			+ (1 - game->step_y) / 2) / game->raydir_y;
	}
}

/*
** calculate height of line to draw on screen
** draw start, end - lowest and highest pixel of line to be drawn
** wall_x - where exactly the wall was hit (used for textures)
** tex_x - x coordinate of where to start pulling tex color
** tex.step - how much to increase tex coordinate per pixel
** to scale to fit wall
** last if statement makes sure texture is not mirrored
*/

void	drawing_specs(t_vars *game)
{
	game->line_height = (int)(game->screen_height / game->perpwalldist);
	game->draw_start = -game->line_height / 2 + game->screen_height / 2;
	if (game->draw_start < 0)
		game->draw_start = 0;
	game->draw_end = game->line_height / 2 + game->screen_height / 2;
	if (game->draw_end >= game->screen_height)
		game->draw_end = game->screen_height - 1;
	if (game->side == 0)
		game->wall_x = game->pos_y + game->perpwalldist * game->raydir_y;
	else
		game->wall_x = game->pos_x + game->perpwalldist * game->raydir_x;
	game->wall_x = game->wall_x - floor((game->wall_x));
	game->tex[game->t].tex_x = (int)(game->wall_x
	* (double)game->tex[game->t].width);
	if ((game->side == 0 && game->raydir_x > 0)
	|| (game->side == 1 && game->raydir_y < 0))
		game->tex[game->t].tex_x = game->tex[game->t].width
		- game->tex[game->t].tex_x - 1;
	game->tex[game->t].step = 1.0 * game->tex[game->t].height
	/ game->line_height;
	game->tex[game->t].tex_pos = (game->draw_start - game->screen_height
	/ 2 + game->line_height / 2) * game->tex[game->t].step;
}

/*
** draw ceiling, walls, then floor
** cast the texture coordinate to integer because
** we can't select color from a float
**
** mask with tex_height - 1 in case of overflow
** ie: if step makes pos larger than texture height
** it will start again from 0
**
** tex_pos - starting y texture coordinate
** - increased by tex step each iteration
*/

void	draw_scene(t_vars *game)
{
	draw_floor_ceiling(game, 'C');
	while (game->draw_line < game->draw_end)
	{
		game->tex[game->t].tex_y = (int)game->tex[game->t].tex_pos;
		if (game->tex[game->t].tex_y > game->tex[game->t].height - 1)
			game->tex[game->t].tex_y = game->tex[game->t].height - 1;
		game->tex[game->t].tex_pos = game->tex[game->t].tex_pos
		+ game->tex[game->t].step;
		game->tex[game->t].get_color = game->tex[game->t].addr
		+ ((game->tex[game->t].tex_y * game->tex[game->t].line_length)
		+ game->tex[game->t].tex_x * (game->tex[game->t].bits_per_pixel / 8));
		game->color = *(unsigned int*)game->tex[game->t].get_color;
		if ((game->color & 0xFF000000) != 0)
			game->color = 0x00000000;
		my_mlx_pixel_put(game, game->ray_x, game->draw_line, game->addr);
		game->draw_line++;
	}
	draw_floor_ceiling(game, 'F');
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycast_sprite.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: smiller <smiller@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/25 17:22:34 by smiller       #+#    #+#                 */
/*   Updated: 2020/11/11 14:13:31 by smiller       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		sprite_dist(t_vars *game)
{
	int			i;

	i = 0;
	while (i < game->num_sprite)
	{
		game->sprite[i].dist = ((game->pos_x - game->sprite[i].x)
		* (game->pos_x - game->sprite[i].x) + (game->pos_y - game->sprite[i].y)
		* (game->pos_y - game->sprite[i].y));
		i++;
	}
}

void		sprite_sort(t_vars *game)
{
	int			i;
	int			count;
	t_sprite	tmp;

	i = 0;
	while (i < game->num_sprite)
	{
		count = 0;
		while (count + i < game->num_sprite)
		{
			if (game->sprite[i].dist < game->sprite[i + count].dist)
			{
				tmp = game->sprite[i];
				game->sprite[i] = game->sprite[i + count];
				game->sprite[i + count] = tmp;
			}
			count++;
		}
		i++;
	}
}

/*
** only draw the sprite if -
** 1) is it in front of you (ahead_behind would be positive)
** 2) it's on the screen (left)
** 3) it's on the screen (right)
** 4) if distance to sprite is smaller than distance to wall
** tex_x - x axis where you start pulling pixel color from
** loop draws every pixel of the current stripe
** 256 and 128 factors to avoid floats
*/

void		sprite_draw(t_vars *game, double *z_buffer)
{
	int	y;
	int	d;

	game->tex[4].tex_x = (int)(256 * (game->draw_start_x -
	(-game->sprite_width / 2 + game->sprite_center_x))
	* game->tex[4].width / game->sprite_width) / 256;
	if (game->ahead_behind > 0 && game->draw_start_x > 0 && game->draw_start_x
	< game->screen_width && game->ahead_behind < z_buffer[game->draw_start_x])
	{
		y = game->draw_start_y;
		while (y < game->draw_end_y)
		{
			d = y * 256 - game->screen_height * 128
			+ game->sprite_height * 128;
			game->tex[4].tex_y = ((d * game->tex[4].height)
			/ game->sprite_height) / 256;
			game->tex[4].get_color = game->tex[4].addr
			+ (game->tex[4].line_length * game->tex[4].tex_y
			+ game->tex[4].tex_x * (game->tex[4].bits_per_pixel / 8));
			game->color = *(unsigned int*)game->tex[4].get_color;
			if ((game->color & 0xFF000000) == 0 && game->color != 0x00000000)
				my_mlx_pixel_put(game, game->draw_start_x, y, game->addr);
			y++;
		}
	}
}

/*
** calculate lowest and highest pixel to fill in current stripe
** calculate height using distance ahead
** calculate width using sprite height and
** the ratio of the tex width to tex height
*/

void		set_sprite_vars(t_vars *game)
{
	game->sprite_height = abs((int)(game->screen_height / game->ahead_behind));
	game->draw_start_y = game->screen_height / 2 - game->sprite_height / 2;
	game->sprite_width = (int)(game->sprite_height
	* ((double)game->tex[4].width / (double)game->tex[4].height));
	if (game->tex[4].width > game->tex[4].height)
		game->sprite_width = game->sprite_height;
	if (game->draw_start_y < 0)
		game->draw_start_y = 0;
	game->draw_end_y = game->screen_height / 2 + game->sprite_height / 2;
	if (game->draw_end_y >= game->screen_height)
		game->draw_end_y = game->screen_height - 1;
	game->draw_start_x = -game->sprite_width / 2 + game->sprite_center_x;
	if (game->draw_start_x < 0)
		game->draw_start_x = 0;
	game->draw_end_x = game->sprite_width / 2 + game->sprite_center_x;
	if (game->draw_end_x >= game->screen_width)
		game->draw_end_x = game->screen_width - 1;
}

/*
** re-calculate sprite coordinates relative to direction player is looking
** translate sprite position relative to camera using inverse camera matrix
**
** if you don't multiply by inverse then we will use the real distance from
** the player position to the sprite position and when the camera rotates,
** the sprite rotates with it which we don't want
*/

void		sprite_translate(t_vars *game, int i)
{
	game->sprite_x = game->sprite[i].x - game->pos_x;
	game->sprite_y = game->sprite[i].y - game->pos_y;
	game->inv = 1.0 / (game->cameraplane_x * game->dir_y
	- game->dir_x * game->cameraplane_y);
	if (game->cardinal_dir == 'S' || game->cardinal_dir == 'W')
		game->right_left = (game->inv * (game->dir_y * game->sprite_x
		- game->dir_x * game->sprite_y) * -1);
	else
		game->right_left = game->inv * (game->dir_y * game->sprite_x
		- game->dir_x * game->sprite_y);
	game->ahead_behind = game->inv * (-game->cameraplane_y * game->sprite_x
	+ game->cameraplane_x * game->sprite_y);
	game->sprite_center_x = (int)(game->screen_width / 2)
	* (1 + game->right_left / game->ahead_behind);
}

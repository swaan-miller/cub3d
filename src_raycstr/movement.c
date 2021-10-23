/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   movement.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smiller <smiller@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/16 13:44:48 by smiller       #+#    #+#                 */
/*   Updated: 2021/10/23 22:12:42 by smiller       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	move_fwd(t_vars *game)
{
	if (game->fwd)
	{
		if (game->map[(int)(game->pos_x + game->dir_x * SPD)]
		[(int)game->pos_y] == '0')
			game->pos_x = game->pos_x + game->dir_x * SPD;
		if (game->map[(int)game->pos_x]
		[(int)(game->pos_y + game->dir_y * SPD)] == '0')
			game->pos_y = game->pos_y + game->dir_y * SPD;
		if (fabs(game->pos_x - (int)game->pos_x) < 0.00000001
		|| floor(game->pos_x - (int)game->pos_x) < 0.00000001)
		{
			if (game->dir_x < 0)
				game->pos_x = game->pos_x + .0001;
			else if (game->dir_x > 0)
				game->pos_x = game->pos_x - .0001;
			else if (game->dir_y < 0)
				game->pos_y = game->pos_y + .0001;
			else if (game->dir_y > 0)
				game->pos_y = game->pos_y - .0001;
		}
	}
}

void	move_back(t_vars *game)
{
	if (game->back)
	{
		if (game->map[(int)(game->pos_x - game->dir_x * SPD)]
		[(int)game->pos_y] == '0')
			game->pos_x = game->pos_x - game->dir_x * SPD;
		if (game->map[(int)game->pos_x]
		[(int)(game->pos_y - game->dir_y * SPD)] == '0')
			game->pos_y = game->pos_y - game->dir_y * SPD;
		if (fabs(game->pos_x - (int)game->pos_x) < 0.00000001
		|| floor(game->pos_x - (int)game->pos_x) < 0.00000001)
		{
			if (game->dir_x < 0)
				game->pos_x = game->pos_x - .0001;
			else if (game->dir_x > 0)
				game->pos_x = game->pos_x + .0001;
			else if (game->dir_y < 0)
				game->pos_y = game->pos_y - .0001;
			else if (game->dir_y > 0)
				game->pos_y = game->pos_y + .0001;
		}
	}
}

void	move_right(t_vars *game)
{
	if (game->right)
	{
		if (game->map[(int)(game->pos_x)]
		[(int)(game->pos_y + (-game->dir_x) * SPD)] == '0')
			game->pos_y = game->pos_y + (-game->dir_x) * SPD;
		if (game->map[(int)(game->pos_x + game->dir_y * SPD)]
		[(int)game->pos_y] == '0')
			game->pos_x = game->pos_x + game->dir_y * SPD;
		if (fabs(game->pos_y - (int)game->pos_y) < 0.00000001
		|| floor(game->pos_y - (int)game->pos_y) < 0.00000001)
		{
			if (game->dir_x < 0)
				game->pos_y = game->pos_y - .0001;
			else if (game->dir_x > 0)
				game->pos_y = game->pos_y + .0001;
			else if (game->dir_y > 0)
				game->pos_x = game->pos_x - .0001;
			else if (game->dir_y < 0)
				game->pos_x = game->pos_x + .0001;
		}
	}
}

void	move_left(t_vars *game)
{
	if (game->left)
	{
		if (game->map[(int)game->pos_x]
		[(int)(game->pos_y - (-game->dir_x) * SPD)] == '0')
			game->pos_y = game->pos_y - (-game->dir_x) * SPD;
		if (game->map[(int)(game->pos_x - game->dir_y * SPD)]
		[(int)game->pos_y] == '0')
			game->pos_x = game->pos_x - game->dir_y * SPD;
		if (fabs(game->pos_y - (int)game->pos_y) < 0.00000001
		|| floor(game->pos_y - (int)game->pos_y) < 0.00000001)
		{
			if (game->dir_x < 0)
				game->pos_y = game->pos_y + .0001;
			else if (game->dir_x > 0)
				game->pos_y = game->pos_y - .0001;
			else if (game->dir_y > 0)
				game->pos_x = game->pos_x + .0001;
			else if (game->dir_y < 0)
				game->pos_x = game->pos_x - .0001;
		}
	}
}

/*
** to rotate player both camera direction and camera plane must be rotated
*/

void	look_right_left(t_vars *game)
{
	if (game->look_right)
	{
		game->old_dir_x = game->dir_x;
		game->dir_x = game->dir_x * cos(-ROT_SPD) - game->dir_y * sin(-ROT_SPD);
		game->dir_y = game->old_dir_x * sin(-ROT_SPD) +
		game->dir_y * cos(-ROT_SPD);
		game->old_cameraplane_x = game->cameraplane_x;
		game->cameraplane_x = game->cameraplane_x * cos(-ROT_SPD) -
		game->cameraplane_y * sin(-ROT_SPD);
		game->cameraplane_y = game->old_cameraplane_x * sin(-ROT_SPD) +
		game->cameraplane_y * cos(-ROT_SPD);
	}
	if (game->look_left)
	{
		game->old_dir_x = game->dir_x;
		game->dir_x = game->dir_x * cos(ROT_SPD) - game->dir_y * sin(ROT_SPD);
		game->dir_y = game->old_dir_x * sin(ROT_SPD) +
		game->dir_y * cos(ROT_SPD);
		game->old_cameraplane_x = game->cameraplane_x;
		game->cameraplane_x = game->cameraplane_x * cos(ROT_SPD) -
		game->cameraplane_y * sin(ROT_SPD);
		game->cameraplane_y = game->old_cameraplane_x * sin(ROT_SPD) +
		game->cameraplane_y * cos(ROT_SPD);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   keys.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: smiller <smiller@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/28 18:38:11 by smiller       #+#    #+#                 */
/*   Updated: 2020/11/05 12:38:21 by swaanmiller   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		push(int keycode, t_vars *game)
{
	if (keycode == 53)
	{
		exit(0);
	}
	if (keycode == 13)
		game->fwd = 1;
	if (keycode == 1)
		game->back = 1;
	if (keycode == 2)
		game->right = 1;
	if (keycode == 0)
		game->left = 1;
	if (keycode == 123)
		game->look_left = 1;
	if (keycode == 124)
		game->look_right = 1;
	return (0);
}

int		release(int keycode, t_vars *game)
{
	if (keycode == 13)
		game->fwd = 0;
	if (keycode == 1)
		game->back = 0;
	if (keycode == 2)
		game->right = 0;
	if (keycode == 0)
		game->left = 0;
	if (keycode == 123)
		game->look_left = 0;
	if (keycode == 124)
		game->look_right = 0;
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smiller <smiller@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/25 17:44:13 by smiller       #+#    #+#                 */
/*   Updated: 2021/10/23 22:12:56 by smiller       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	arg_error_check(t_vars *game, int argc, char **argv)
{
	int		cub;

	if (argc < 2)
		error("Too few arguments.");
	if (argc > 3)
		error("Too many arguments.");
	if (argc == 3)
	{
		if ((ft_strncmp(argv[2], "--save", 7) != 0))
			error("Try using --save to make a screenshot.");
		game->screenshot = 1;
	}
	cub = ft_strlen(argv[1]);
	if (ft_strncmp(".cub", argv[1] + (cub - 4), 4) != 0)
		error("This is not a cub file.");
}

void	my_mlx_pixel_put(t_vars *game, int x, int y, char *addr)
{
	char	*dst;

	dst = addr + (y * game->line_length + x * (game->bits_per_pixel / 8));
	*(unsigned int*)dst = game->color;
}

void	set_wall_tex(t_vars *game)
{
	if (game->side == 0 && game->raydir_x < 0)
		game->t = 0;
	if (game->side == 0 && game->raydir_x > 0)
		game->t = 1;
	if (game->side == 1 && game->raydir_y > 0)
		game->t = 2;
	if (game->side == 1 && game->raydir_y < 0)
		game->t = 3;
}

int		exit_game(void)
{
	exit(0);
}

void	draw_floor_ceiling(t_vars *game, char area)
{
	if (area == 'C')
	{
		while (game->draw_start > game->draw_line)
		{
			game->color = game->ceiling;
			my_mlx_pixel_put(game, game->ray_x, game->draw_line, game->addr);
			game->draw_line++;
		}
	}
	if (area == 'F')
	{
		while (game->screen_height > game->draw_line)
		{
			game->color = game->floor;
			my_mlx_pixel_put(game, game->ray_x, game->draw_line, game->addr);
			game->draw_line++;
		}
	}
}

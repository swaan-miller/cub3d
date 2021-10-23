/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   driver.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: smiller <smiller@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/16 13:44:48 by smiller       #+#    #+#                 */
/*   Updated: 2020/11/08 20:17:24 by smiller       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
** find distance from each sprite to player
** sort them from furthest to closest
** translate sprite coordinates depending on dir player facing
** set variables for drawing
** draw sprites by looping through every
** vertical stripe of the sprite on screen
** perpwalldist is used for sprites because you always look them head on
*/

static void	sprite_casting(t_vars *game, double *z_buffer)
{
	int		i;

	i = 0;
	sprite_dist(game);
	sprite_sort(game);
	while (i < game->num_sprite)
	{
		sprite_translate(game, i);
		set_sprite_vars(game);
		while (game->draw_start_x < game->draw_end_x)
		{
			sprite_draw(game, z_buffer);
			game->draw_start_x++;
		}
		i++;
	}
}

/*
** camera_x is the x coordinate on the camera plane
** camera_x goes from -1 to 1 across the camera plane
** and there is one camera_x for each ray_x
** set the zbuffer for the sprite casting
** zbuffer holds perpwalldist of each ray
*/

static void	raycasting(t_vars *game)
{
	game->z_buffer = ft_calloc(game->screen_width, sizeof(double));
	if (game->z_buffer == NULL)
		error("Malloc for z_buffer failed.");
	game->ray_x = 0;
	while (game->ray_x < game->screen_width)
	{
		game->camera_x = 2 * game->ray_x / (double)game->screen_width - 1;
		raydir_deltadist(game);
		sidedist(game);
		wall_hit(game);
		set_wall_tex(game);
		drawing_specs(game);
		game->draw_line = 0;
		draw_scene(game);
		game->z_buffer[game->ray_x] = game->perpwalldist;
		game->ray_x++;
	}
	sprite_casting(game, game->z_buffer);
	free(game->z_buffer);
}

/*
** render image and put image to window
*/

static int	render_frame(t_vars *game)
{
	if (game->fwd || game->back || game->right || game->left
	|| game->look_right || game->look_left)
	{
		move_fwd(game);
		move_back(game);
		move_right(game);
		move_left(game);
		look_right_left(game);
		raycasting(game);
		mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
		mlx_destroy_image(game->mlx, game->img);
		game->img = mlx_new_image(game->mlx, game->screen_width,
		game->screen_height);
		game->addr = mlx_get_data_addr(game->img, &game->bits_per_pixel,
		&game->line_length, &game->endian);
	}
	return (0);
}

static void	set_vars(t_cub *scene, t_vars *game)
{
	mlx_get_screen_size(game->mlx, &game->screen_width, &game->screen_height);
	set_screen_vars(game, scene);
	set_player_vars(game, scene);
	set_tex_vars(game, scene);
	game->sprite = ft_calloc(game->num_sprite, sizeof(t_sprite));
	if (game->sprite == NULL)
		error("Sprite memory allocation failed.");
	set_map(game, scene);
}

void		game_loop(t_vars *game, t_cub *scene)
{
	game->mlx = mlx_init();
	parse_cub(scene);
	close(scene->fd);
	set_vars(scene, game);
	game->win = mlx_new_window(game->mlx, scene->res_width,
				scene->res_height, "cub3d");
	game->img = mlx_new_image(game->mlx, scene->res_width, scene->res_height);
	game->addr = mlx_get_data_addr(game->img, &game->bits_per_pixel,
				&game->line_length, &game->endian);
	raycasting(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	if (game->screenshot == 1)
		save_screenshot(game);
	mlx_destroy_image(game->mlx, game->img);
	game->img = mlx_new_image(game->mlx, game->screen_width,
	game->screen_height);
	game->addr = mlx_get_data_addr(game->img, &game->bits_per_pixel,
	&game->line_length, &game->endian);
	mlx_hook(game->win, 2, 1L << 0, push, game);
	mlx_hook(game->win, 3, 1L << 1, release, game);
	mlx_hook(game->win, 17, 1L << 0, exit_game, game);
	mlx_hook(game->win, 17, 1L << 2, exit_game, game);
	mlx_loop_hook(game->mlx, render_frame, game);
	mlx_loop(game->mlx);
}

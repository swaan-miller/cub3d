/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: smiller <smiller@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/25 19:53:49 by smiller       #+#    #+#                 */
/*   Updated: 2020/11/03 09:52:06 by smiller       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int			main(int argc, char **argv)
{
	t_cub	scene;
	t_vars	game;

	ft_bzero(&scene, sizeof(t_cub));
	ft_bzero(&game, sizeof(t_vars));
	arg_error_check(&game, argc, argv);
	scene.fd = open(argv[1], O_RDWR);
	if (scene.fd == ERROR)
		error("Error opening cub file.");
	game_loop(&game, &scene);
	return (0);
}

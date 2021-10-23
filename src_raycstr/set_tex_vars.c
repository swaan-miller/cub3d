/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_tex_vars.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: smiller <smiller@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/04 19:28:14 by smiller       #+#    #+#                 */
/*   Updated: 2020/11/08 20:15:26 by smiller       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static char	*tex_path(t_cub *scene, int i)
{
	if (i == 0)
		return (scene->path.nrth);
	if (i == 1)
		return (scene->path.south);
	if (i == 2)
		return (scene->path.east);
	if (i == 3)
		return (scene->path.wst);
	if (i == 4)
		return (scene->path.sprt);
	return (0);
}

void		set_tex_vars(t_vars *game, t_cub *scene)
{
	char	*path;
	int		i;

	i = 0;
	game->num_sprite = scene->num_sprites;
	while (i < 5)
	{
		path = tex_path(scene, i);
		scene->path.len = ft_strlen(path);
		if (ft_strncmp(".xpm", path + scene->path.len - 4, 4) == 0)
			game->tex[i].img = mlx_xpm_file_to_image(game->mlx, path,
			&game->tex[i].width, &game->tex[i].height);
		else if (ft_strncmp(".png", path + scene->path.len - 4, 4) == 0)
			game->tex[i].img = mlx_png_file_to_image(game->mlx, path,
			&game->tex[i].width, &game->tex[i].height);
		else
			error("Not a valid file. Try xpm or png.");
		if (game->tex[i].img == NULL)
			error("Invalid texture file.");
		game->tex[i].addr = mlx_get_data_addr(game->tex[i].img, &game->
		tex[i].bits_per_pixel, &game->tex[i].line_length, &game->tex[i].endian);
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_checks.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: smiller <smiller@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/08 10:30:34 by smiller       #+#    #+#                 */
/*   Updated: 2021/10/23 22:13:10 by smiller       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		error(char *reason)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(reason, 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}

void	check_elements(t_cub *scene)
{
	if ((ft_strncmp(scene->error, "R ", 2) == 0) && scene->typeid.res == ON)
		error("Duplicate resolution input.");
	if ((ft_strncmp(scene->error, "F ", 2) == 0) && scene->typeid.floor == ON)
		error("Duplicate floor color input.");
	if ((ft_strncmp(scene->error, "C ", 2) == 0) && scene->typeid.ceiling == ON)
		error("Duplicate ceiling color input.");
	if (scene->typeid.res == OFF)
		error("Resolution missing.");
	if (scene->typeid.floor == OFF)
		error("Floor color missing.");
	if (scene->typeid.ceiling == OFF)
		error("Ceiling color missing.");
	if (scene->path.sprt == NULL)
		error("Sprite texture path missing.");
	if (scene->path.nrth == NULL)
		error("North texture path missing.");
	if (scene->path.south == NULL)
		error("South texture path missing.");
	if (scene->path.east == NULL)
		error("East texture path missing.");
	if (scene->path.wst == NULL)
		error("West texture path missing.");
	error("Invalid type identifier.");
}

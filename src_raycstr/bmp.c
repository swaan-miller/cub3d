/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bmp.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: smiller <smiller@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/22 20:04:21 by smiller       #+#    #+#                 */
/*   Updated: 2020/11/10 21:48:18 by smiller       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	get_pixels(t_vars *game, int image_size)
{
	char	*dest;
	int		y;
	int		x;
	int		i;

	i = 0;
	y = game->screen_height - 1;
	game->pixel_buf = ft_calloc(image_size, sizeof(int));
	if (game->pixel_buf == NULL)
		error("Malloc for pixel_buf failed");
	while (y >= 0)
	{
		x = 0;
		while (x < game->screen_width)
		{
			dest = game->addr + (y * game->line_length + x
			* (game->bits_per_pixel / 8));
			game->pixel_buf[i] = *(unsigned int*)dest;
			i++;
			x++;
		}
		y--;
	}
}

static void	convert_int(int i, unsigned char *int_byte)
{
	int_byte[0] = (unsigned char)(i);
	int_byte[1] = (unsigned char)(i >> 8);
	int_byte[2] = (unsigned char)(i >> 16);
	int_byte[3] = (unsigned char)(i >> 24);
}

static void	create_header(t_vars *game, int fd, int file_size)
{
	unsigned char	header_buf[54];
	int				ret;

	ft_bzero(&header_buf, 54);
	header_buf[0] = 'B';
	header_buf[1] = 'M';
	convert_int(file_size, &header_buf[2]);
	convert_int(54, &header_buf[10]);
	convert_int(40, &header_buf[14]);
	convert_int(game->screen_width, &header_buf[18]);
	convert_int(game->screen_height, &header_buf[22]);
	convert_int(1, &header_buf[26]);
	convert_int(game->bits_per_pixel, &header_buf[28]);
	convert_int(file_size - 54, &header_buf[34]);
	ret = write(fd, header_buf, 54);
	if (ret == ERROR)
		error("Failed to create BMP header");
}

int			save_screenshot(t_vars *game)
{
	int		image_size;
	int		fd;
	int		ret;

	image_size = (game->screen_height * game->screen_width
	* (game->bits_per_pixel / 8));
	fd = open("screenshot.bmp", O_RDWR | O_CREAT, 0644);
	if (fd == ERROR)
		error("Failed to open screenshot.bmp");
	create_header(game, fd, image_size + 54);
	get_pixels(game, image_size);
	ret = write(fd, game->pixel_buf, image_size);
	if (ret == ERROR)
		error("BMP write failed");
	exit(0);
}

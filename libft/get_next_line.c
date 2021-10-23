/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: smiller <smiller@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 14:13:36 by smiller       #+#    #+#                 */
/*   Updated: 2020/09/08 12:11:13 by smiller       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	new_line(char *str, char *buf, char **line)
{
	int		i;
	int		y;

	i = 0;
	y = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	*line = ft_substr(str, 0, i);
	if (*line == NULL)
	{
		free(str);
		return (-1);
	}
	while (buf[y] != '\n' && buf[y] != '\0')
		y++;
	if (buf[y] == '\n')
	{
		ft_memmove(buf, buf + y + 1, ft_strlen(buf) - y);
		free(str);
		return (1);
	}
	free(str);
	return (0);
}

static char	*join(char *str, char *buf)
{
	char	*tmp;

	tmp = ft_strjoin(str, buf);
	if (tmp == NULL)
	{
		free(str);
		return (NULL);
	}
	free(str);
	return (tmp);
}

int			get_next_line(int fd, char **line)
{
	static char	buf[OPEN_MAX][BUFFER_SIZE + 1];
	char		*str;
	ssize_t		rd;

	rd = 1;
	if (fd < 0 || line == NULL || BUFFER_SIZE == 0)
		return (-1);
	str = ft_strdup(buf[fd]);
	if (str == NULL)
		return (-1);
	while (rd > 0 && ft_strchr(buf[fd], '\n') == NULL)
	{
		rd = read(fd, buf[fd], BUFFER_SIZE);
		if (rd == -1)
		{
			free(str);
			return (-1);
		}
		buf[fd][rd] = '\0';
		str = join(str, buf[fd]);
		if (str == NULL)
			return (-1);
	}
	return (new_line(str, buf[fd], line));
}

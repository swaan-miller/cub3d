/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: smiller <smiller@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/12 11:45:32 by smiller       #+#    #+#                 */
/*   Updated: 2020/06/02 08:39:36 by smiller       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	char	*hay;
	char	*need;

	i = 0;
	hay = (char*)haystack;
	need = (char*)needle;
	if (need[i] == '\0')
		return (hay);
	while (len > i && hay[i])
	{
		j = 0;
		if (need[j] == hay[i])
		{
			while ((hay[j + i] == need[j]) && (i + j < len))
			{
				j++;
				if (need[j] == '\0')
					return (&hay[i]);
			}
		}
		i++;
	}
	return (NULL);
}

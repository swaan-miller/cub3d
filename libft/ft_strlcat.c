/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: smiller <smiller@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/12 11:39:16 by smiller       #+#    #+#                 */
/*   Updated: 2020/05/20 13:51:55 by smiller       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dst == NULL && dstsize == 0)
		return (ft_strlen(src));
	while (dst[i] && dstsize > i)
		i++;
	if (i + 1 < dstsize)
		ft_strlcpy(&dst[i], src, dstsize - i);
	return (i + ft_strlen(src));
}

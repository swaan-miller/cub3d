/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: smiller <smiller@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/12 11:36:12 by smiller       #+#    #+#                 */
/*   Updated: 2020/04/27 11:04:52 by smiller       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned const char	*s;
	unsigned char		*d;
	size_t				i;

	s = src;
	d = dst;
	i = 0;
	if (n == 0 || d == s)
		return (d);
	while (n > i)
	{
		d[i] = s[i];
		i++;
	}
	return (d);
}

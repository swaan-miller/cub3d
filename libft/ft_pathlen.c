/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_pathlen.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: smiller <smiller@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/24 11:57:02 by smiller       #+#    #+#                 */
/*   Updated: 2020/10/25 18:02:36 by smiller       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_pathlen(const char *s)
{
	size_t	i;

	i = 0;
	while (ft_isprint(s[i]) && s[i] != ' ')
		i++;
	return (i);
}

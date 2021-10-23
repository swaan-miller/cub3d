/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: smiller <smiller@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/20 13:40:51 by smiller       #+#    #+#                 */
/*   Updated: 2020/05/22 13:00:45 by smiller       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		len;

	start = 0;
	if (s1 == NULL)
		return (NULL);
	if (s1[start] == '\0' || set == NULL)
		return (ft_strdup(s1));
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	len = ft_strlen(s1);
	while (len > 0 && ft_strchr(set, s1[len]))
		len--;
	if (len == 0)
		return (ft_strdup(""));
	return (ft_substr(s1, start, len - start + 1));
}

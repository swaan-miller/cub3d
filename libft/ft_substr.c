/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: smiller <smiller@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/20 08:37:14 by smiller       #+#    #+#                 */
/*   Updated: 2020/05/14 15:17:48 by smiller       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*str;
	char			*substr;
	unsigned int	i;

	i = 0;
	str = (char*)s;
	if (s == NULL)
		return (NULL);
	if (start > ft_strlen(str))
		return (ft_strdup(""));
	if ((start + len) > ft_strlen(str))
		len = ft_strlen(str) - start;
	substr = ft_calloc(len + 1, sizeof(char));
	if (substr == NULL)
		return (NULL);
	while (str[i] && i < len)
	{
		substr[i] = str[start + i];
		i++;
	}
	substr[len] = '\0';
	return (substr);
}

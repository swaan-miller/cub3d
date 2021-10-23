/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: smiller <smiller@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/20 11:21:28 by smiller       #+#    #+#                 */
/*   Updated: 2020/05/14 14:00:04 by smiller       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*cat;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	cat = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (cat == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		cat[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		cat[i] = s2[j];
		j++;
		i++;
	}
	cat[i] = '\0';
	return (cat);
}

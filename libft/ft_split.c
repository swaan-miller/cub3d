/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smiller <smiller@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/22 15:34:26 by smiller       #+#    #+#                 */
/*   Updated: 2020/05/14 16:19:12 by smiller       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_word_count(char const *s, char c)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (s == 0)
		return (0);
	if (s[0] != c)
		j++;
	while (s[i])
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			j++;
		i++;
	}
	return (j);
}

static char	**free_all(char **str, int a)
{
	while (a - 1 >= 0)
	{
		free(str[a - 1]);
		a--;
	}
	free(str);
	return (NULL);
}

static char	**ft_get_substr(char **str, char const *s, char c)
{
	size_t	i;
	size_t	j;
	int		a;

	i = 0;
	a = 0;
	while (i < (ft_strlen(s)))
	{
		while (s[i] == c && s[i])
			i++;
		j = i;
		while (s[i] != c && s[i])
			i++;
		if (j == i)
			return (str);
		str[a] = ft_substr(s, j, i - j);
		if (str[a] == NULL)
		{
			free_all(str, a);
			return (NULL);
		}
		a++;
		i++;
	}
	return (str);
}

char		**ft_split(char const *s, char c)
{
	char	**str;
	int		words;

	if (s == NULL)
		return (NULL);
	words = ft_word_count(s, c);
	str = ft_calloc(words + 1, sizeof(char*));
	if (str == NULL)
		return (NULL);
	str = ft_get_substr(str, s, c);
	if (str == NULL)
		return (NULL);
	str[words] = NULL;
	return (str);
}

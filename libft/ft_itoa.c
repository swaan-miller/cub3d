/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: smiller <smiller@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/25 14:09:39 by smiller       #+#    #+#                 */
/*   Updated: 2020/05/14 14:28:40 by smiller       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_num(char *str, int n, int i, int y)
{
	if (n == -2147483648)
	{
		str[0] = '-';
		str[1] = 2 + '0';
		n = 147483648;
		y = 2;
	}
	else if (n < 0)
	{
		str[0] = '-';
		n = n * -1;
		y = 1;
	}
	if (n < 10 && n >= 0)
		str[y] = (n % 10 + '0');
	else if (n > 9 && n <= 2147483647)
	{
		ft_num(str, n / 10, i - 1, y);
		y = i - 1;
		str[y] = (n % 10 + '0');
	}
	return (str);
}

char		*ft_itoa(int n)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = n;
	if (n <= 0)
		i = 1;
	while (j != 0)
	{
		j = j / 10;
		i++;
	}
	str = ft_calloc(i + 1, sizeof(char));
	if (str == NULL)
		return (NULL);
	str = ft_num(str, n, i, j);
	str[i] = '\0';
	return (str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: smiller <smiller@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/12 11:27:42 by smiller       #+#    #+#                 */
/*   Updated: 2020/05/20 09:21:32 by smiller       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int					sign;
	int					value;
	int					i;

	sign = 1;
	value = 0;
	i = 0;
	while (((str[i] >= 8 && str[i] <= 13) || str[i] == ' ' ||
		(str[i] == '+' && str[i + 1] >= '0' && str[i + 1] <= '9')))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		value = (value * 10) + (str[i] - '0');
		i++;
	}
	return (value * sign);
}

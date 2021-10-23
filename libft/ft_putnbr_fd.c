/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnbr_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: smiller <smiller@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/26 16:28:14 by smiller       #+#    #+#                 */
/*   Updated: 2020/05/12 09:58:45 by smiller       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		ft_putchar_fd('-', fd);
		ft_putchar_fd(2 + '0', fd);
		ft_putnbr_fd(147483648, fd);
	}
	else if (n < 0 && n > -2147483648)
	{
		ft_putchar_fd('-', fd);
		ft_putnbr_fd(n * -1, fd);
	}
	if (n < 10 && n >= 0)
		ft_putchar_fd(n % 10 + '0', fd);
	else if (n > 9 && n <= 2147483647)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putchar_fd(n % 10 + '0', fd);
	}
}

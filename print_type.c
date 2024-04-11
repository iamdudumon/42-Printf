/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeonsan.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 15:40:31 by dukim             #+#    #+#             */
/*   Updated: 2024/04/06 15:40:33 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "print_utils.h"

int	ft_putchar(const char ch)
{
	write(1, &ch, 1);
	return (1);
}

int	ft_putstr(const char *str)
{
	size_t	len;

	if (!str)
	{
		write(1, "(null)", 6);
		return (6);
	}
	len = ft_strlen(str);
	write(1, str, len);
	return (len);
}

int	ft_putnbr(int n, int sign_flag)
{
	char				nbr[12];
	unsigned int		pow;
	unsigned int		un;
	size_t				i;

	if (n == 0)
		return (ft_putchar('0'));
	i = 0;
	un = n;
	if (sign_flag && n < 0)
	{
		un = -n;
		nbr[i++] = '-';
	}
	else if (!sign_flag && n < 0)
		un = n + 2147483648 * 2;
	pow = pow_ten(un);
	while (pow)
	{
		nbr[i++] = (un / pow) + '0';
		un = un % pow;
		pow /= 10;
	}
	write(1, nbr, i);
	return (i);
}

int	ft_puthex(unsigned long n, int case_flag, int addr_flag)
{
	char	*hex;
	char	str[16];
	size_t	i;
	int		size;

	hex = "0123456789ABCDEF";
	if (case_flag)
		hex = "0123456789abcdef";
	size = 8;
	if (addr_flag)
		size = 16;
	i = 0;
	while (1)
	{
		str[size - 1 - i++] = hex[n % 16];
		n = n / 16;
		if (n == 0)
			break ;
	}
	write(1, str + size - i, i);
	return (i);
}

int	ft_putaddr(const void *addr)
{
	if (!addr)
	{
		ft_putstr("(nil)");
		return (5);
	}
	write(1, "0x", 2);
	return (ft_puthex((unsigned long)addr, 1, 1) + 2);
}

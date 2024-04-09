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

void    ft_putchar(const char ch)
{
    write(1, &ch, 1);
}

void    ft_putstr(const char *str)
{
    size_t len;

    len = ft_strlen(str);
    write(1, str, len);
}

void	ft_putnbr(int n)
{
	char				nbr[12];
	unsigned int		pow;
	unsigned int		un;
	size_t				i;

	i = 0;
	if (n < 0)
	{
		un = -n;
		nbr[i++] = '-';
	}
	else
		un = n;
	pow = pow_ten(un);
	while (pow)
	{
		nbr[i++] = (un / pow) + '0';
		un = un % pow;
		pow /= 10;
	}
	nbr[i] = '\0';
	if (i == 0)
		ft_putstr("0");
    else
        ft_putstr(nbr);
}

void	ft_puthex(unsigned long n, int case_flag, int addr_flag)
{
	char	*hex;
	char	str[16];
	size_t	i;
	int		size;

	if (case_flag)
		hex = "0123456789abcdef";
	else
		hex = "0123456789ABCDEF";
	if (size)
		size = 16;
	else
		size = 8;
	i = 0;
	while (1)
	{
		str[size - 1 - i++] = hex[n % 16];
		n = n / 16;
		if (n == 0)
			break;
	}
	write(1, str + size - i, i);
}

void    ft_putaddr(const void *addr)
{
	write(1, "0x", 2);
	ft_puthex((unsigned long)addr, 1, 1);
}
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

t_specifier	*ft_putchar(const char ch)
{
	t_specifier	*spec;
	char		str[2];
	
	spec = (t_specifier *)malloc(sizeof(t_specifier));
	if (!spec)
		return (0);
	str[0] = ch;
	str[1] = '\0';
	spec->str = ft_strdup(str);
	spec->len = 1;
	return (spec);
}

t_specifier	*ft_putstr(const char *str)
{
	t_specifier	*spec;

	spec = (t_specifier *)malloc(sizeof(t_specifier));
	if (!spec)
		return (0);
	if (!str)
	{
		spec->str = ft_strdup("(null)");
		spec->len = 6;
		return (spec);
	}
	spec->str = ft_strdup(str);
	spec->len = ft_strlen(str);
	return (spec);
}

t_specifier	*ft_putnbr(int n, int sign_flag)
{
	t_specifier			*spec;
	char				nbr[12];
	unsigned int		pow;
	unsigned int		un;

	if (n == 0)
		return (ft_putchar('0'));
	spec = (t_specifier *)malloc(sizeof(t_specifier));
	if (!spec)
		return (0);
	spec->len = 0;
	un = n;
	if (sign_flag && n < 0)
	{
		un = -n;
		nbr[spec->len++] = '-';
	}
	else if (!sign_flag && n < 0)
		un = n + 2147483648 * 2;
	pow = pow_ten(un);
	while (pow)
	{
		nbr[spec->len++] = (un / pow) + '0';
		un = un % pow;
		pow /= 10;
	}
	nbr[spec->len] = '\0';
	spec->str = ft_strdup(nbr);
	return (spec);
}

t_specifier	*ft_puthex(unsigned long n, int case_flag, int addr_flag)
{
	t_specifier	*spec;
	char	*hex;
	char	str[17];
	int		size;

	spec = (t_specifier *)malloc(sizeof(t_specifier));
	if (!spec)
		return (0);
	spec->len = 0;
	hex = "0123456789ABCDEF";
	if (case_flag)
		hex = "0123456789abcdef";
	size = 8;
	if (addr_flag)
		size = 16;
	str[size] = '\0';
	while (1)
	{
		str[size - 1 - spec->len++] = hex[n % 16];
		n = n / 16;
		if (n == 0)
			break ;
	}
	spec->str = ft_strdup(str + size - spec->len);
	return (spec);
}

t_specifier	*ft_putaddr(const void *addr)
{
	t_specifier	*spec;
	t_specifier	*tmp;

	spec = (t_specifier *)malloc(sizeof(t_specifier));
	if (!spec)
		return (0);
	if (!addr)
	{
		spec->str = ft_strdup("(nil)");
		spec->len = 5;
		return (spec);
	}
	tmp = ft_puthex((unsigned long)addr, 1, 1);
	spec->str = ft_strjoin("0x", tmp->str);
	spec->len = 2 + tmp->len;
	free(tmp->str);
	free(tmp);
	return (spec);
}

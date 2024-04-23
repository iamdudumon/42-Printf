/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_diu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 21:43:50 by dukim             #+#    #+#             */
/*   Updated: 2024/04/20 21:43:51 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	pow_ten(unsigned int un)
{
	unsigned int	pow;

	if (un >= 1000000000)
		return (1000000000);
	pow = 1;
	while (pow <= un)
		pow *= 10;
	return (pow / 10);
}

static char *make_zero_precision(int precision_len)
{
	char *zero;

	if (precision_len <= 0)
	{
		zero = ft_strdup("");
		return (zero);
	}
	zero = (char *)malloc(precision_len + 1);
    ft_memset(zero, '0', precision_len);
	zero[precision_len] = '\0';
	return (zero);
}

static char *make_nbr_str(int n, int sign_flag)
{
	char				nbr[12];
	unsigned int		pow;
	unsigned int		un;
	int				i;

	if (n == 0)
		return (ft_strdup("0"));
	i = 0;
	un = n;
	if (sign_flag && n < 0)
		un = -n;
	if (!sign_flag && n < 0)
		un = n + 2147483648 * 2;
	pow = pow_ten(un);
	while (pow)
	{
		nbr[i++] = (un / pow) + '0';
		un = un % pow;
		pow /= 10;
	}
	nbr[i] = '\0';
	return (ft_strdup(nbr));
}

t_specifier	ft_putnbr(t_format *format, int n, int sign_flag)
{
	t_specifier			spec;
    char                *zero;
    char                *nbr;

	if (format->precision_flag)
        format->zero_flag = 0;
	if (format->plus_flag)
		format->blank_flag = 0;
    spec.sign_ch = '+';
	if (sign_flag && n >= 0 && format->blank_flag)
	{
		spec.sign_ch = ' ';
		format->blank_flag= 0;
		format->plus_flag = 1;
	}
	if (sign_flag && n < 0)
        spec.sign_ch = '-';
    nbr = make_nbr_str(n, sign_flag);
	if (*nbr == '0' && (format->precision_flag && !format->precision))
	{
		spec.str = ft_strdup("");
		spec.len = ft_strlen(spec.str);
		free(nbr);
		return (spec);
	}
	zero = make_zero_precision(format->precision - (int)ft_strlen(nbr));
    spec.str = ft_strjoin(zero, nbr);
	spec.len = ft_strlen(spec.str);
    free(nbr);
    free(zero);
	return (spec);
}
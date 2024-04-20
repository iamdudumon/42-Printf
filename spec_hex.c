/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spec_addr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 23:43:28 by dukim             #+#    #+#             */
/*   Updated: 2024/04/20 23:43:29 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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

static char *make_hex_str(unsigned long n, int case_flag, int addr_flag)
{
    char    str[17];
    char    *hex;
    int size;
    int len;

    hex = "0123456789abcdef";
    size = 16;
	if (!case_flag)
		hex = "0123456789ABCDEF";
	if (!addr_flag)
	    size = 8;
    len = 0;
    str[size] = '\0';
	while (1)
	{
		str[size - 1 - len++] = hex[n % 16];
		n = n / 16;
		if (n == 0)
			break ;
	}
    return (ft_strdup(str + size - len));
}

t_specifier	ft_puthex(t_format *format, unsigned long n, int case_flag, int addr_flag)
{
	t_specifier	spec;
    char    *zero;
	char	*hex_str;

    if (format->precision_flag)
        format->zero_flag = 0;
    hex_str = make_hex_str(n, case_flag, addr_flag);
    if (*hex_str == '0' && (format->precision_flag && !format->precision))
	{
		spec.str = ft_strdup("");
		spec.len = ft_strlen(spec.str);
		free(hex_str);
		return (spec);
	}
    zero = make_zero_precision(format->precision - (int)ft_strlen(hex_str));
    spec.str = ft_strjoin(zero, hex_str);
	spec.len = ft_strlen(spec.str);
    free(zero);
    free(hex_str);
	return (spec);
}

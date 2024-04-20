/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:55:01 by dukim             #+#    #+#             */
/*   Updated: 2024/04/16 14:55:03 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_specifier *set_specifier(char type, va_list args)
{
    if (type == 'c')
        return ft_putchar(va_arg(args, int));
    if (type == 's')
        return ft_putstr(va_arg(args, char *));
    if (type == 'd' || type == 'i' || type == 'u')
        return ft_putnbr(va_arg(args, int), type != 'u');
    if (type == 'p')
        return ft_putaddr(va_arg(args, void *));
    if (type == 'X' || type == 'x')
        return ft_puthex(va_arg(args, unsigned int), type == 'x', 0);
    if (type == '%')
        return ft_putchar('%');
    return (0);
}

void print_width(int width, int zero_flag)
{
    char ch;

    if (width <= 0)
        return;
    ch = ' ';
    if (zero_flag)
        ch = '0';
    while (width > 0)
    {
        write(1, &ch, 1);
        width--;
    }
}

t_format make_format(const char *str, va_list args)
{
    t_format format;

    format.plus_flag = 0;
    format.minus_flag = 0;
    format.zero_flag = 0;
    format.flag_cnt = 0;
    format.width_len = 0;
    format.error_flag = 0;
    while (*str == '+' || *str == '-' || *str == '0')
    {
        if (*str == '+')
            format.plus_flag++;
        if (*str == '-')
            format.minus_flag++;
        if (*str == '0')
            format.zero_flag++;
        str++;
    }
    format.flag_cnt = format.plus_flag + format.minus_flag + format.zero_flag;
    while ('0' <= *str && *str <= '9')
    {
        format.width_len++;
        str++;
    }
    format.width = ft_atoi(str - format.width_len, format.width_len);
    format.spec = set_specifier(*str, args);
    format.specifier = *str;
    if (!format.spec)
        format.error_flag = 1;
    return (format);
}

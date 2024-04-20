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

static void set_flag(t_format *format)
{
    if (!format->spec.str)
        format->error_flag = 1;
    if (format->spec.sign_ch == '-')
        format->plus_flag = 1;
    if (format->plus_flag && (format->specifier != 'd' && format->specifier != 'i'))
        format->plus_flag = 0;
    if (format->zero_flag && format->minus_flag)
        format->zero_flag= 0;
}

t_specifier make_specifier(t_format *format, char type, va_list args)
{
    t_specifier temp;

    if (type == 'c')
        temp = ft_putchar(va_arg(args, int));
    if (type == 's')
        temp = ft_putstr(format, va_arg(args, char *));
    if (type == 'd' || type == 'i' || type == 'u')
        temp = ft_putnbr(format, va_arg(args, int), type != 'u');
    if (type == 'p')
        temp = ft_putaddr(format, va_arg(args, void *));
    if (type == 'X' || type == 'x')
        temp = ft_puthex(format, va_arg(args, unsigned int), type == 'x', 0);
    if (type == '%')
        temp = ft_putchar('%');
    return (temp);
}

t_format make_format(const char *str, va_list args)
{
    t_format format;
    int width_len;
    int precision_len;

    ft_memset(&format, 0, sizeof(t_format));
    width_len = 0;
    precision_len = 0;
    while (*str == '+' || *str == '-' || *str == '0')
    {
        if (*str == '+')
            format.plus_flag++;
        if (*str == '-')
            format.minus_flag++;
        if (*str == '0')
            format.zero_flag++;
        format.size++;
        str++;
    }
    while ('0' <= *str && *str <= '9')
    {
        width_len++;
        format.size++;
        str++;
    }
    format.width = ft_atoi(str - width_len);
    if (*str == '.')
    {
        str++;
        format.size++;
        format.precision_flag++;
        while ('0' <= *str && *str <= '9')
        {
            precision_len++;
            format.size++;
            str++;
        }
    }
    format.precision = ft_atoi(str - precision_len);
    format.spec = make_specifier(&format, *str, args);
    format.specifier = *str;
    set_flag(&format);
    return (format);
}

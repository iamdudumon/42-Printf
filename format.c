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
    if (!format->spec)
        format->error_flag = 1;
    if (format->spec->sign_ch == '-')
        format->plus_flag = 1;
    if (format->plus_flag && (format->specifier != 'd' && format->specifier != 'i'))
        format->plus_flag = 0;
    if (format->zero_flag && format->minus_flag)
        format->zero_flag= 0;
}

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
    char    *buffer;
    char    ch;

    if (width <= 0)
        return;
    buffer = (char *)malloc(sizeof(char) * width);
    ch = ' ';
    if (zero_flag)
        ch = '0';
    ft_memset(buffer, ch, width);
    write(1, buffer, width);
    free(buffer);
}

t_format make_format(const char *str, va_list args)
{
    t_format format;
    int width_len;

    ft_memset(&format, 0, sizeof(t_format));
    width_len = 0;
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
    format.width = ft_atoi(str - width_len, width_len);
    format.spec = set_specifier(*str, args);
    format.specifier = *str;
    set_flag(&format);
    return (format);
}

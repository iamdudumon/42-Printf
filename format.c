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

t_format    make_format(const char *str)
{
    t_format    format;
    int         width_len;
    
    format.flag_cnt = 0;
    while (*str == "-" || *str == '+' || *str == '0')
    {
        format.flag[format.flag_cnt++] = *str;
        *str++;
    }
    width_len = 0;
    while ('0' <= *str && *str <= '0')
        width_len++;
    format.width = ft_atoi(*str, width_len);
    str += width_len;
    format.spec.specifier = *str;
    set_specifier(str, &(format.spec));
    return (format);
}

void	set_specifier(const char *str, t_specifier *spec)
{
	if (spec->specifier == '\0')
        spec->len = 0;
    if (spec->specifier == 'c')
		spec = ft_putchar(va_arg(args, int));
	if (spec->specifier == 's')
		spec = ft_putstr(va_arg(args, char *));
	if (spec->specifier == 'd' || spec->specifier == 'i' || spec->specifier == 'u')
		spec = ft_putnbr(va_arg(args, int), spec->specifier != 'u');
	if (spec->specifier == 'p')
		spec = ft_putaddr(va_arg(args, void *));
	if (spec->specifier == 'X' || spec->specifier == 'x')
		spec = ft_puthex(va_arg(args, unsigned int), spec->specifier == 'x', 0);
	if (spec->specifier == '%')
		spec = ft_putchar('%');
	if (*(str + 1) != '\0')
		spec = ft_putchar('%');
	return (-1);
}

void    print_width(int width, int zero_flag)
{
    char    ch;

    ch = ' ';
    if (zero_flag)
        ch = '0';
    while (width > 0)
    {
        write(1, &ch, 1);
        width--;
    }
}
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
    set_specifier(str, &(format.spec), *str);
    return (format);
}

void	set_specifier(const char *str, t_type *spec, char type)
{
	if (type == '\0')
        spec->len = 0;
    if (type == 'c')
		spec = ft_putchar(va_arg(args, int));
	if (type == 's')
		spec = ft_putstr(va_arg(args, char *));
	if (type == 'd' || type == 'i' || type == 'u')
		spec = ft_putnbr(va_arg(args, int), type != 'u');
	if (type == 'p')
		spec = ft_putaddr(va_arg(args, void *));
	if (type == 'X' || type == 'x')
		spec = ft_puthex(va_arg(args, unsigned int), type == 'x', 0);
	if (type == '%')
		spec = ft_putchar('%');
	if (*(str + 1) != '\0')
		spec = ft_putchar('%');
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
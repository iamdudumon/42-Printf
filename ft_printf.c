/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeonsan.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 16:41:00 by dukim             #+#    #+#             */
/*   Updated: 2024/04/04 16:57:37 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void    store_buffer(char *buf, size_t *buf_len, char ch)
{
    if (*buf_len == BUFFER_SIZE)
        ft_putstr(buf);
    buf[*buf_len] = ch;
    buf[*buf_len + 1] = '\0';
    (*buf_len)++;
}

void    clean_buffer(char *buf, size_t *buf_len, int *res)
{
    if (*buf_len > 0)
    {
        ft_putstr(buf);
        *res += *buf_len;
        *buf_len = 0;
    }
}

int    print_format(char format, va_list args)
{
    const char *enable_format = "cspdiuxX";
 
    if (format == 'c')
        ft_putchar(va_arg(args, int));
    else if (format == 's')
        ft_putstr(va_arg(args, char *));
    else if (format == 'd' || format == 'i' || format == 'u')
        ft_putnbr(va_arg(args, int), format != 'u');
    else if (format == 'p')
        ft_putaddr(va_arg(args, void *));
    else if (format == 'X' || format == 'x')
        ft_puthex(va_arg(args, unsigned int), format == 'x', 0);
    else if (format == '%')
        ft_putchar('%');
    return (0);
}

int	ft_printf(const char *str, ...)
{
    va_list args;
    char    buf[BUFFER_SIZE];
    size_t  buf_len;
    int     res;

    va_start(args, str);
    buf_len = 0;
    res = 0;
    while (*str != '\0')
    {
        if (*str == '%')
        {
            clean_buffer(buf, &buf_len, &res);
            print_format(*(++str), args);
            str++;
            continue;
        }
        store_buffer(buf, &buf_len, *str);
        str++;
    }
    clean_buffer(buf, &buf_len, &res);
    return (res);
}

#include <stdio.h>
int main(){
    // ft_printf("%d\n", 2147483648);
    // printf("%d\n", 2147483648);

    // ft_printf("%%\n", -2);
    // printf("%%\n", -2);

    // ft_printf("%p\n", -1);
    // printf("%p\n", -1);

    // ft_printf("%s\n", 0);
    // printf("%s\n", 0);

    int n = printf("%d %d\n", 5, 6);
    int n2 = ft_printf("%d %d\n", 5, 6);
    printf("%d %d\n", n, n2);
}

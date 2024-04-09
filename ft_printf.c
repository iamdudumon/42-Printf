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

void    clean_buffer(char *buf, size_t *buf_len)
{
    if (*buf_len > 0)
    {
        ft_putstr(buf);
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
    return (0);
}

int	ft_printf(const char *str, ...)
{
    va_list args;
    char    buf[BUFFER_SIZE];
    size_t  buf_len;

    va_start(args, str);
    buf_len = 0;
    while (*str != '\0')
    {
        if (*str == '%')
        {
            clean_buffer(buf, &buf_len);
            print_format(*(++str), args);
            str++;
            continue;
        }
        store_buffer(buf, &buf_len, *str);
        str++;
    }
    ft_putstr(buf);
    return (buf_len);
}



// void print(const char *str, ...)
// {
//     va_list args;

//     va_start(args, str);
//     ft_printf("%d %d %d hihihihhisaldjsald %c\n", args);
//     va_end(args);

//     va_start(args, str);
//     printf("%d %d %d hihihihhisaldjsald %c\n", args);
//     va_end(args);
// }
#include <stdio.h>
int main(){
    // ft_printf("%d %d %d hihihihhisaldjsald %c\n", 1, 2, "a", "a");
    // printf("%d %d %d hihihihhisaldjsald %c\n", 1, 2, "a", "a");
    // int n = 5;
    // ft_printf("%p\n", &n);
    // printf("%p\n", &n);
    // int hex = 2147483648;
    // ft_printf("%d\n", 2147483648);
    // printf("%d\n", 2147483648);

    ft_printf("%u\n", -2);
    printf("%u\n", -2);

    // ft_printf("%p\n", -1);
    // printf("%p\n", -1);

    // ft_printf("%s\n", 0);
    // printf("%s\n", 0);
}

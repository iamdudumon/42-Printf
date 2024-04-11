/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeonsan.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 16:41:00 by dukim             #+#    #+#             */
/*   Updated: 2024/04/11 17:51:38 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	clean_buffer(t_buffer *buf, int *res)
{
	if (buf->len > 0)
	{
		ft_putstr(buf->content);
		*res += buf->len;
		buf->len = 0;
	}
}

void	store_buffer(t_buffer *buf, int *res, char ch)
{
	if (buf->len == BUFFER_SIZE)
		clean_buffer(buf, res);
	buf->content[buf->len] = ch;
	buf->content[buf->len + 1] = '\0';
	(buf->len)++;
}

int	print_format(char **str, va_list args)
{
	char	*format;

	format = *str + 1;
	(*str)++;
	if (*format == '\0')
		return (0);
	(*str)++;
	if (*format == 'c')
		return (ft_putchar(va_arg(args, int)));
	if (*format == 's')
		return (ft_putstr(va_arg(args, char *)));
	if (*format == 'd' || *format == 'i' || *format == 'u')
		return (ft_putnbr(va_arg(args, int), *format != 'u'));
	if (*format == 'p')
		return (ft_putaddr(va_arg(args, void *)));
	if (*format == 'X' || *format == 'x')
		return (ft_puthex(va_arg(args, unsigned int), *format == 'x', 0));
	if (*format == '%')
		return (ft_putchar('%'));
	if (*(format + 1) != '\0')
		return (ft_putchar('%'));
	return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list		args;
	t_buffer	buf;
	int			res;
	int			error_flag;

	va_start(args, str);
	buf.len = 0;
	res = 0;
	error_flag = 1;
	while (*str != '\0')
	{
		if (*str == '%')
		{
			clean_buffer(&buf, &res);
			error_flag = print_format((char **)&str, args);
			res += error_flag;
			continue ;
		}
		store_buffer(&buf, &res, *str);
		str++;
	}
	clean_buffer(&buf, &res);
	if (error_flag == 0)
		return (-1);
	return (res);
}

// #include <stdio.h>
// int main(){
//     int n1, n2;

//     n1= ft_printf("%d\n", 0);
//     n2 = printf("%d\n", 0);
//     printf("%d %d\n", n1, n2);

//     n1= ft_printf("%u\n", 2147483648 + 2147483648 - 1);
//     n2 = printf("%u\n", 2147483648 + 2147483648 - 1);
//     printf("%d %d\n", n1, n2);

//     ft_printf("%%\n", -2);
//     printf("%%\n", -2);

//     ft_printf("%p\n", -1);
//     printf("%p\n", -1);

//     ft_printf("%s\n", 0);
//     printf("%s\n", 0);

//     n1 = printf("123456789012345678901234567890123456789012345678901234567980\n");
//     n2 = ft_printf("123456789012345678901234567890123456789012345678901234567980\n");
//     printf("%d %d\n", n1, n2);

//     n1 = ft_printf("myname is %s\nmy age: %d, my sex: %c\n", "dukim", 25, 'm');
//     n2 = printf("myname is %s\nmy age: %d, my sex: %c\n", "dukim", 25, 'm');
//     printf("%d %d\n", n1, n2);

//     ft_printf("%s\t\t---%p\n", 0, 0);
//     printf("%s\t\t---%p\n", 0, 0);

//     ft_printf("%x %X\n", 23408230948230, -111);
//     printf("%x %X\n", 23408230948230, -111);

//     n1 = ft_printf("%d %z", 5, 5);
//     printf("%d\n", n1);
//     n2 = printf("%d %z", 5, 5);
//     printf("%d\n", n2);
// }

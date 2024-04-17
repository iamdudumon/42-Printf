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

static void	clean_buffer(t_buffer *buf, int *res)
{
	if (buf->len > 0)
	{
		write(1, buf->content, buf->len);
		*res += buf->len;
		buf->len = 0;
	}
}

static void	store_buffer(t_buffer *buf, int *res, char ch)
{
	if (buf->len == BUFFER_SIZE)
		clean_buffer(buf, res);
	buf->content[buf->len] = ch;
	buf->content[buf->len + 1] = '\0';
	(buf->len)++;
}

static void	init_val(t_buffer *buf, int *res, int *error_flag)
{
	buf->len = 0;
	*res = 0;
	*error_flag = 1;
}

static int	print_format(char **str, va_list args)
{
	t_format	format;
	int			res;

	if (**str == '\0')
		return (-1);
	format = make_format(*str, args);
	if (format.error_flag == 1)
		return (-1);
	(*str) += format.flag_cnt + format.width_len + 1;
	res = format.spec->len;
	write(1, format.spec->str, format.spec->len);
	free(format.spec->str);
	free(format.spec);
	return (res);
	
}

int	ft_printf(const char *str, ...)
{
	va_list		args;
	t_buffer	buf;
	int			res;
	int			error_flag;

	va_start(args, str);
	init_val(&buf, &res, &error_flag);
	while (*str != '\0')
	{
		if (*str == '%')
		{
			clean_buffer(&buf, &res);
			str++;
			error_flag = print_format((char **)&str, args);
			if (error_flag == -1)
				return (-1);
			res += error_flag;
			continue ;
		}
		store_buffer(&buf, &res, *str);
		str++;
	}
	clean_buffer(&buf, &res);
	return (res);
}

#include <stdio.h>
int main(){
    int n1, n2;

    // n1= ft_printf("%d\n", 0);
    // n2 = printf("%d\n", 0);

    // n1= ft_printf("%u\n", 2147483648 + 2147483648 - 1);
    // n2 = printf("%u\n", 2147483648 + 2147483648 - 1);

    // ft_printf("%%\n", -2);
    // printf("%%\n", -2);

    // ft_printf("%p\n", -1);
    // printf("%p\n", -1);

    // ft_printf("%s\n", 0);
    // printf("%s\n", 0);

    // n1 = printf("123456789012345678901234567890123456789012345678901234567980\n");
    // n2 = ft_printf("123456789012345678901234567890123456789012345678901234567980\n");


    // n1 = ft_printf("myname is %s\nmy age: %d, my sex: %c\n", "dukim", 25, 'm');
    // n2 = printf("myname is %s\nmy age: %d, my sex: %c\n", "dukim", 25, 'm');


    // ft_printf("%s\t\t---%p\n", 0, 0);
    // printf("%s\t\t---%p\n", 0, 0);

    // ft_printf("%x %X\n", 23408230948230, -111);
    // printf("%x %X\n", 23408230948230, -111);

    // n1 = ft_printf("%d %z", 5, 5);
    // printf("%d\n", n1);
    // n2 = printf("%d %z", 5, 5);

	// int n = ft_printf("hihih %      ");
	// printf("res: %d\n", n);

	n1 = ft_printf("%c%c%c ", 0, 1, 0);
	n2 = printf("%c%c%c ", 0, 1, 0);
    printf("%d %d\n", n1, n2);
}
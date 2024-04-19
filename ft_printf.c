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

static void print_final_format(t_format format)
{
	if (!format.minus_flag)
	{
		if (format.plus_flag == 0)
			print_width(format.width - format.spec->len - format.plus_flag, format.zero_flag);
		if (format.plus_flag == 1 && format.zero_flag == 1)
		{
			write(1, "+", 1);
			print_width(format.width - format.spec->len - format.plus_flag, format.zero_flag);
		}
		if (format.plus_flag == 1 && format.zero_flag == 0)
		{
			print_width(format.width - format.spec->len - format.plus_flag, format.zero_flag);
			write(1, "+", 1);
		}
		write(1, format.spec->str, format.spec->len);
	}
	if (format.minus_flag)
	{
		if (format.plus_flag == 1)
			write(1, "+", 1);
		write(1, format.spec->str, format.spec->len);
		print_width(format.width - format.spec->len - format.plus_flag, 0);
	}
}
static int print_format(char **str, va_list args, int *res)
{
	t_format format;

	if (**str == '\0')
		return (-1);
	format = make_format(*str, args);
	if (format.error_flag == 1)
		return (0);
	(*str) += format.flag_cnt + format.width_len + 1;
	if (format.width - format.spec->len - format.plus_flag <= 0)
		*res += format.plus_flag + format.spec->len;
	else
		*res += format.width;
	print_final_format(format);
	free(format.spec->str);
	free(format.spec);
	return (1);
}

int ft_printf(const char *str, ...)
{
	va_list args;
	t_buffer buf;
	int res;

	va_start(args, str);
	buf.len = 0;
	res = 0;
	while (*str != '\0')
	{
		if (*str == '%')
		{
			clean_buffer(&buf, &res);
			str++;
			if (!print_format((char **)&str, args, &res))
				return (-1);
			continue;
		}
		store_buffer(&buf, &res, *str);
		str++;
	}
	clean_buffer(&buf, &res);
	return (res);
}

#include <stdio.h>
int main()
{
	int n1, n2;

	// n1= ft_printf("%d\n", 0);
	// n2 = printf("%d\n", 0);

	// n1= ft_printf("%u\n", 2147483648 + 2147483648 - 1);
	// n2 = printf("%u\n", 2147483648 + 2147483648 - 1);

	// ft_printf("%%\n", -2);
	// printf("%%\n", -2);

	// ft_printf("%p\n", &n1);
	// printf("%p\n", &n1);

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

	// n1 = ft_printf("%c%c%c%", '\0', 1, 0);
	// n2 = printf("%c%c%c%", '\0', 1, 0);

	// n1 = ft_printf("%+d\n", 2147483647);
	// n2 = printf("%+d\n", 2147483647);

	// n1 = ft_printf("%-d\n", 1234);
	// n2 = printf("%-d\n", 1234);

	// printf("%d %d\n", n1, n2);

	int n = ft_printf("%--c", 'a');
	printf("\n%d\n", n);
}

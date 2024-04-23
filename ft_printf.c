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

static void print_width(int width, int zero_flag)
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

static void print_final_format(t_format format)
{
	if (!format.minus_flag)
	{
		if (format.zero_flag && format.plus_flag)
			ft_putchar_fd(format.spec.sign_ch, 1);
		print_width(format.width - format.spec.len - (format.plus_flag != 0), format.zero_flag);
		if (!format.zero_flag && format.plus_flag)
			ft_putchar_fd(format.spec.sign_ch, 1);
		write(1, format.spec.str, format.spec.len);
	}
	if (format.minus_flag)
	{
		if (format.plus_flag)
			ft_putchar_fd(format.spec.sign_ch, 1);
		write(1, format.spec.str, format.spec.len);
		print_width(format.width - format.spec.len - (format.plus_flag != 0), format.zero_flag);
	}
}
static int print_format(char **str, va_list args, int *res)
{
	t_format	format;

	if (**str == '\0')
		return (-1);
	format = make_format(*str, args);
	if (format.error_flag == 1)
		return (0);
	*str += format.size + 1;
	if (format.width - format.spec.len - (format.plus_flag != 0) <= 0)
		*res += (format.plus_flag != 0) + format.spec.len;
	else
		*res += format.width;
	print_final_format(format);
	free(format.spec.str);
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

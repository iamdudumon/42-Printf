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
		ft_putstr(buf->content);
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

static int	print_format(char **str, va_list args)
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
	return (-1);
}

static void	init_val(t_buffer *buf, int *res, int *error_flag)
{
	buf->len = 0;
	*res = 0;
	*error_flag = 1;
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
			error_flag = print_format((char **)&str, args);
			if (error_flag != -1)
				res += error_flag;
			continue ;
		}
		store_buffer(&buf, &res, *str);
		str++;
	}
	clean_buffer(&buf, &res);
	if (error_flag == -1)
		return (-1);
	return (res);
}

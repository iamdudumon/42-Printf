/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeonsan.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 16:29:50 by dukim             #+#    #+#             */
/*   Updated: 2024/04/11 17:47:02 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
#define FT_PRINTF_H

#define BUFFER_SIZE 42

#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>

typedef struct s_buffer
{
	char		content[BUFFER_SIZE];
	int			len;
}				t_buffer;

typedef struct s_specifier
{
	char		*str;
	int			len;
}				t_specifier;

typedef struct s_format
{
	char		specifier;
	char		plus_flag;
	char		minus_flag;
	char		zero_flag;
	char		error_flag;
	char		sign_ch;
	int			width;
	int			size;
	t_specifier	*spec;
}				t_format;

int			ft_printf(const char *str, ...);

void		clean_buffer(t_buffer *buf, int *res);
void		store_buffer(t_buffer *buf, int *res, char ch);

t_specifier	*ft_putchar(const char ch);
t_specifier *ft_putstr(const char *str);
t_specifier *ft_putnbr(int n, int sign_flag);
t_specifier *ft_putaddr(const void *addr);
t_specifier *ft_puthex(unsigned long n, int case_flag, int addr_flag);

int			pow_ten(unsigned int un);
int			ft_strlen(const char *str);
int			ft_atoi(const char *nptr, int len);
char		*ft_strdup(const char *s);
char		*ft_strjoin(const char *s1, const char *s2);
void		*ft_memset(void *s, int c, size_t n);

t_format	make_format(const char *str, va_list args);
void		print_width(int width, int zero_flag);

#endif

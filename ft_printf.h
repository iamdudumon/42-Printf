/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeonsan.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 16:29:50 by dukim             #+#    #+#             */
/*   Updated: 2024/04/04 16:40:47 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# define BUFFER_SIZE 42

# include "libft/libft.h"

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

int ft_putchar(const char ch);
int ft_putstr(const char *str);
int ft_putnbr(int n, int sign_flag);
int ft_putaddr(const void *addr);
int ft_puthex(unsigned long n, int case_flag, int addr_flag);

#endif

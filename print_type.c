/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeonsan.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 15:40:31 by dukim             #+#    #+#             */
/*   Updated: 2024/04/06 15:40:33 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

void    ft_putchar(const char ch)
{
    write(1, &ch, 1);
}

void    ft_putstr(const char *str)
{
    size_t len;

    len = ft_strlen(str);
    write(1, str, len);
}

static int	pow_ten(unsigned int un)
{
	unsigned int	pow;

	if (un >= 1000000000)
		return (1000000000);
	pow = 1;
	while (pow <= un)
		pow *= 10;
	return (pow / 10);
}

void	ft_putnbr(int n)
{
	char				nbr[12];
	unsigned int		pow;
	unsigned int		un;
	size_t				i;

	i = 0;
	if (n < 0)
	{
		un = -n;
		nbr[i++] = '-';
	}
	else
		un = n;
	pow = pow_ten(un);
	while (pow)
	{
		nbr[i++] = (un / pow) + '0';
		un = un % pow;
		pow /= 10;
	}
	nbr[i] = '\0';
	if (i == 0)
		ft_putstr("0");
    else
        ft_putstr(nbr);
}

void    ft_putaddr(const void *addr)
{
    
}
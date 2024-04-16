/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeonsan.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:29:02 by dukim             #+#    #+#             */
/*   Updated: 2024/04/11 17:40:37 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	pow_ten(unsigned int un)
{
	unsigned int	pow;

	if (un >= 1000000000)
		return (1000000000);
	pow = 1;
	while (pow <= un)
		pow *= 10;
	return (pow / 10);
}

size_t	ft_strlen(const char *str)
{
	const char	*ori;

	ori = str;
	while (*str != '\0')
		str++;
	return (str - ori);
}

int	ft_atoi(const char *nptr, int len)
{
	int	sum;

	sum = 0;
	while (len > 0 && ('0' <=*nptr && *nptr <= '9'))
	{
		sum = sum * 10 + (*nptr - '0');
		nptr++;
		len--;
	}
	return (sum);
}

char	*ft_strdup(const char *s)
{
	char	*dup;
	size_t	len;

	len = ft_strlen(s);
	dup = (char *)malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (0);
	while (*str != '\0')
	{
		*dup = *str;
		dup++;
		str++;
	}
	return (dup);
}

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

int	ft_strlen(const char *str)
{
	const char	*ori;

	ori = str;
	while (*str != '\0')
		str++;
	return (str - ori);
}

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

int	ft_atoi(const char *nptr, int len)
{
	int	sum;

	if (len == 0)
		return (0);
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
	while (*s != '\0')
	{
		*dup = *s;
		dup++;
		s++;
	}
	return (dup - len);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*join_str;
	size_t	s1_len;
	size_t	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	join_str = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!join_str)
		return (0);
	while (*s1 == '\0')
	{
		*join_str = *s1;
		join_str++;
		s1++;
	}
	while (*s2 == '\0')
	{
		*join_str = *s2;
		join_str++;
		s2++;
	}
	*join_str = '\0';
	return (join_str);
}

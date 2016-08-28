/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmicolon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/02 22:42:49 by rmicolon          #+#    #+#             */
/*   Updated: 2015/12/04 15:16:10 by rmicolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_printnbr(char *s, unsigned int n, size_t i)
{
	if (n >= 10)
	{
		ft_printnbr(s, n / 10, i - 1);
		ft_printnbr(s, n % 10, i);
	}
	else
		s[i] = n + 48;
}

char		*ft_itoa(int n)
{
	size_t			i;
	unsigned int	m;
	int				sign;
	char			*s;

	i = 1;
	sign = 0;
	if (n < 0)
	{
		i++;
		sign = 1;
		n = -n;
	}
	m = n;
	while ((m /= 10) > 0)
		i++;
	if (!(s = (char*)malloc(sizeof(*s) * (i + 1))))
		return (NULL);
	if (sign == 1)
		s[0] = '-';
	ft_printnbr(s, n, i - 1);
	s[i] = '\0';
	return (s);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmicolon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/30 12:51:11 by rmicolon          #+#    #+#             */
/*   Updated: 2016/02/19 18:38:04 by rmicolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
 
static char		*ft_allocstr(int value, int base)
{
	int		count;
	char	*str;

	count = 0;
	if (value < 0 && base == 10)
		count++;
	if (value < 0)
		value *= -1;
	if (value == 0)
		count++;
	while (value > 0)
	{
		value /= base;
		count++;
	}
	if (!(str = (char *)malloc(sizeof(*str) * count + 1)))
		return (NULL);
	return (str);
}

static char		*ft_returnzero(void)
{
	char *zero;

	if (!(zero = (char *)malloc(sizeof(*zero) * 2)))
		return (NULL);
	zero[0] = '0';
	zero[1] = '\0';
	return (zero);
}

char			*ft_itoa_base(int value, int base)
{
	char	*str;
	int		i;
	int		isneg;

	if (base < 2 || base > 16 || value == 0)
		return (ft_returnzero());
	if (!(str = ft_allocstr(value, base)))
		return (NULL);
	i = 0;
	isneg = 0;
	if (base == 10 && value < 0)
		isneg = 1;
	while (value != 0)
	{
		if (value % base <= 9)
			str[i++] = ft_abs(value % base) + '0';
		else
			str[i++] = (ft_abs(value % base) - 10) + 'a';
		value /= base;
	}
	if (isneg)
		str[i++] = '-';
	str[i] = '\0';
	ft_strrev(str);
	return (str);
}

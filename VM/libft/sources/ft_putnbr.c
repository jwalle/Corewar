/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmicolon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 19:21:04 by rmicolon          #+#    #+#             */
/*   Updated: 2015/12/04 15:16:29 by rmicolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putposn(unsigned int n)
{
	if (n >= 10)
	{
		ft_putposn(n / 10);
		ft_putposn(n % 10);
	}
	else
		ft_putchar(n + 48);
}

void		ft_putnbr(int n)
{
	if (n < 0)
	{
		n = -n;
		ft_putchar('-');
	}
	ft_putposn(n);
}

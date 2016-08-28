/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xtox.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmicolon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 19:26:29 by rmicolon          #+#    #+#             */
/*   Updated: 2016/03/14 15:29:34 by rmicolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned long long int	ft_stou(signed long long int nb, t_pf *pf)
{
	if (nb < 0)
	{
		pf->neg = 1;
		nb += 1;
		nb *= -1;
		return (nb + 1);
	}
	return (nb);
}

long double				ft_dtold(double nb, t_pf *pf)
{
	if (nb < 0)
	{
		pf->neg = 1;
		nb *= -1;
	}
	return (nb);
}

long double				ft_ldtold(long double nb, t_pf *pf)
{
	if (nb < 0)
	{
		pf->neg = 1;
		nb *= -1;
	}
	return (nb);
}

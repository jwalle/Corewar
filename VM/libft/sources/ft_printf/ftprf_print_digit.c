/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_digit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmicolon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 19:25:49 by rmicolon          #+#    #+#             */
/*   Updated: 2016/03/14 18:54:37 by rmicolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_printhex(t_pf *pf)
{
	write(pf->fd, "0x", 2);
	pf->ret += 2;
}

void		ft_print_zeros(char base, t_pf *pf)
{
	int	tsize;

	tsize = (pf->nsize >= pf->prec) ? pf->nsize : pf->prec;
	if (pf->plus == 1 || pf->neg == 1 || pf->space == 1)
		tsize++;
	if (pf->sharp == 1 && base == 16)
		tsize += 2;
	if (pf->sharp == 1 && base == 8)
		tsize++;
	while (tsize < pf->width)
	{
		ft_printchar('0', pf);
		tsize++;
	}
}

void		ft_print_numprec(unsigned long long int nb, char base, t_pf *pf)
{
	int size;

	size = 1;
	while (nb >= (size_t)base)
	{
		nb /= base;
		size++;
	}
	while (size < pf->prec)
	{
		ft_printchar('0', pf);
		size++;
	}
}

void		ft_printnbr(unsigned long long int nb, char base, t_pf *pf)
{
	if (nb >= (size_t)base)
	{
		ft_printnbr(nb / base, base, pf);
		ft_printnbr(nb % base, base, pf);
	}
	else
	{
		if (nb <= 9)
			ft_printchar(nb + '0', pf);
		else if (nb > 9 && pf->maj == 1)
			ft_printchar((nb - 10) + 'A', pf);
		else
			ft_printchar((nb - 10) + 'a', pf);
		pf->tsc++;
		if (pf->ts == 1 && pf->tsc % 3 == 0
				&& pf->tsc < pf->nsize + 1 && base == 10)
			ft_printchar(',', pf);
	}
}

void		ft_printfloat(long double nb, t_pf *pf)
{
	int					i;
	unsigned long long	intpart;

	intpart = (unsigned long long)nb;
	ft_printnbr(intpart, 10, pf);
	nb -= intpart;
	if (!(pf->dot == 1 && pf->prec == 0))
		ft_printchar('.', pf);
	i = 0;
	while (i++ < pf->prec)
		nb *= 10;
	ft_print_numprec((unsigned long long)(nb + 0.5), 10, pf);
	ft_printnbr((unsigned long long)(nb + 0.5), 10, pf);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_digitflags.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmicolon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 19:25:29 by rmicolon          #+#    #+#             */
/*   Updated: 2016/03/16 00:17:08 by rmicolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			ft_nsize(unsigned long long int nb, char base, t_pf *pf)
{
	while (nb >= (size_t)base)
	{
		nb /= base;
		pf->nsize++;
	}
}

static void		ft_thosep(t_pf *pf)
{
	pf->tsc = 3 - (pf->nsize % 3);
	pf->width -= (pf->nsize % 3 == 0) ? (pf->nsize / 3) - 1 : pf->nsize / 3;
	pf->prec -= (pf->nsize % 3 == 0) ? (pf->nsize / 3) - 1 : pf->nsize / 3;
}

void			ft_pre_unumflags(unsigned long long int nb, char base, t_pf *pf)
{
	ft_nsize(nb, base, pf);
	if (pf->plus == 1 && pf->neg == 0 && pf->width > 0)
		pf->width++;
	if (pf->ts == 1 && base == 10)
		ft_thosep(pf);
	if (pf->width > 0 && pf->minus == 0 && (pf->zero == 0 || pf->dot == 1))
		ft_print_numwidth(nb, base, pf);
	if (pf->neg == 1)
		ft_printchar('-', pf);
	if (nb && pf->sharp == 1 && base == 16)
	{
		ft_printchar('0', pf);
		if (pf->maj == 1)
			ft_printchar('X', pf);
		else
			ft_printchar('x', pf);
	}
	if (nb && pf->sharp == 1 && base == 8 && (pf->dot == 0 || pf->prec == 0))
		ft_printchar('0', pf);
	if (nb && pf->sharp == 1 && base == 2)
		ft_print_prefix("0b", pf);
	if (pf->zero == 1 && pf->dot == 0 && pf->minus == 0)
		ft_print_zeros(base, pf);
	if (pf->prec > 0)
		ft_print_numprec(nb, base, pf);
}

void			ft_pre_numflags(unsigned long long int nb, char base, t_pf *pf)
{
	ft_nsize(nb, base, pf);
	if (pf->space == 1 && pf->neg == 0 && pf->plus == 0)
		ft_printchar(' ', pf);
	if (pf->ts == 1 && base == 10)
		ft_thosep(pf);
	if (pf->width > 0 && pf->minus == 0 && (pf->zero == 0 || pf->dot == 1))
		ft_print_numwidth(nb, base, pf);
	if (pf->plus == 1 && pf->neg == 0)
		ft_printchar('+', pf);
	if (pf->neg == 1)
		ft_printchar('-', pf);
	if (pf->zero == 1 && pf->dot == 0 && pf->minus == 0)
		ft_print_zeros(base, pf);
	if (pf->prec > 0)
		ft_print_numprec(nb, base, pf);
}

void			ft_pre_floatflags(long double nb, t_pf *pf)
{
	if (pf->width > pf->prec && pf->minus == 0)
		ft_print_floatwidth(nb, pf);
	if (pf->neg == 1)
		ft_printchar('-', pf);
}

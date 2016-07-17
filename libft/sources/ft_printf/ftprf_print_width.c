/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_width.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmicolon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 19:26:04 by rmicolon          #+#    #+#             */
/*   Updated: 2016/03/15 21:29:44 by rmicolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_print_strwidth(char *str, t_pf *pf)
{
	int	ssize;
	int	tsize;

	ssize = 0;
	if (str)
		ssize = ft_strlen(str);
	if (pf->dot == 1 && ssize > pf->prec)
		tsize = pf->prec;
	else
		tsize = ssize;
	while (tsize < pf->width)
	{
		if (pf->zero == 1)
			ft_printchar('0', pf);
		else
			ft_printchar(' ', pf);
		tsize++;
	}
}

void		ft_print_wstrwidth(wchar_t *str, t_pf *pf)
{
	int	ssize;
	int	tsize;

	ssize = 0;
	if (str)
		ssize = ft_wwidthlen(str);
	if (pf->dot == 1 && ssize > ft_wideprec(str, pf))
		tsize = ft_wideprec(str, pf);
	else
		tsize = ssize;
	while (tsize < pf->width)
	{
		if (pf->zero == 1)
			ft_printchar('0', pf);
		else
			ft_printchar(' ', pf);
		tsize++;
	}
}

void		ft_print_charwidth(t_pf *pf)
{
	int	tsize;

	tsize = 1;
	while (tsize < pf->width)
	{
		if (pf->zero == 1)
			ft_printchar('0', pf);
		else
			ft_printchar(' ', pf);
		tsize++;
	}
}

void		ft_print_numwidth(unsigned long long nb, char base, t_pf *pf)
{
	int nsize;
	int	tsize;

	nsize = 1;
	if (nb == 0 && pf->dot == 1 && pf->prec == 0)
		nsize = 0;
	while (nb >= (size_t)base)
	{
		nb /= base;
		nsize++;
	}
	tsize = (nsize >= pf->prec) ? nsize : pf->prec;
	if (pf->plus == 1 || pf->neg == 1 || pf->space == 1)
		tsize++;
	if (pf->sharp == 1 && base == 16)
		tsize += 2;
	if (pf->sharp == 1 && base == 8)
		tsize++;
	while (tsize < pf->width)
	{
		ft_printchar(' ', pf);
		tsize++;
	}
}

void		ft_print_floatwidth(long double nb, t_pf *pf)
{
	int nsize;
	int tsize;

	nsize = 1;
	if (nb == 0 && pf->dot == 1 && pf->prec == 0)
		nsize = 0;
	while (nb >= 10)
	{
		nb /= 10;
		nsize++;
	}
	tsize = nsize + pf->prec + 1;
	while (tsize < pf->width)
	{
		if (pf->zero == 1)
			ft_printchar('0', pf);
		else
			ft_printchar(' ', pf);
		tsize++;
	}
}

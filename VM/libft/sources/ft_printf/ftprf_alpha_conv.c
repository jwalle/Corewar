/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alpha_conv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmicolon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 19:24:33 by rmicolon          #+#    #+#             */
/*   Updated: 2016/03/16 00:13:37 by rmicolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_print_s(t_pf *pf)
{
	if (pf->len == 3)
	{
		pf->ls = va_arg(pf->argp, wchar_t *);
		if (!pf->ls)
			pf->ls = L"(null)";
		ft_pre_wstrflags(pf->ls, pf);
		ft_printwstr(pf->ls, pf);
		ft_post_wstrflags(pf->ls, pf);
	}
	else
	{
		pf->s = va_arg(pf->argp, char *);
		if (!pf->s)
			pf->s = "(null)";
		ft_pre_strflags(pf->s, pf);
		ft_printstr(pf->s, pf);
		ft_post_strflags(pf->s, pf);
	}
}

void		ft_print_sup(t_pf *pf)
{
	pf->ls = va_arg(pf->argp, wchar_t *);
	if (!pf->ls)
	{
		pf->ls = L"(null)";
	}
	ft_pre_wstrflags(pf->ls, pf);
	ft_printwstr(pf->ls, pf);
	ft_post_wstrflags(pf->ls, pf);
}

void		ft_print_c(t_pf *pf)
{
	if (pf->len == 3)
	{
		pf->lc = va_arg(pf->argp, wchar_t);
		ft_pre_wcharflags(pf->lc, pf);
		ft_printwchar(pf->lc, pf);
		ft_post_wcharflags(pf->lc, pf);
	}
	else
	{
		pf->i = va_arg(pf->argp, int);
		ft_pre_charflags(pf);
		ft_printchar(pf->i, pf);
		ft_post_charflags(pf);
	}
}

void		ft_print_cup(t_pf *pf)
{
	pf->lc = va_arg(pf->argp, wchar_t);
	ft_pre_wcharflags(pf->lc, pf);
	ft_printwchar(pf->lc, pf);
	ft_post_wcharflags(pf->lc, pf);
}

void		ft_print_p(t_pf *pf)
{
	pf->sharp = 1;
	pf->u = va_arg(pf->argp, unsigned long long int);
	ft_nsize(pf->u, 16, pf);
	if (pf->plus == 1 && pf->neg == 0 && pf->width > 0)
		pf->width++;
	if (pf->width > 0 && pf->minus == 0 && (pf->zero == 0 || pf->dot == 1))
		ft_print_numwidth(pf->u, 16, pf);
	if (pf->u == 0 && (pf->zero == 1 || pf->prec > 0))
		ft_printhex(pf);
	if (pf->u && pf->sharp == 1)
		ft_print_prefix("0x", pf);
	if (pf->zero == 1 && pf->dot == 0 && pf->minus == 0)
		ft_print_zeros(16, pf);
	if (pf->prec > 0)
		ft_print_numprec(pf->u, 16, pf);
	if (pf->u == 0 && pf->zero == 0 && pf->prec == 0)
		ft_printhex(pf);
	if (!(pf->u == 0 && pf->dot == 1 && pf->prec == 0))
		ft_printnbr(pf->u, 16, pf);
	ft_post_numflags(pf->u, 16, pf);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xof_conv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmicolon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 19:26:23 by rmicolon          #+#    #+#             */
/*   Updated: 2016/03/15 20:46:35 by rmicolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_print_o(t_pf *pf)
{
	if (pf->len == 3)
		pf->u = va_arg(pf->argp, unsigned long);
	else if (pf->len == 4 || pf->len == 7)
		pf->u = va_arg(pf->argp, unsigned long long);
	else if (pf->len == 5)
		pf->u = va_arg(pf->argp, uintmax_t);
	else if (pf->len == 6)
		pf->u = va_arg(pf->argp, size_t);
	else
		pf->u = va_arg(pf->argp, unsigned int);
	ft_pre_unumflags(pf->u, 8, pf);
	if (!(pf->u == 0 && pf->dot == 1 && pf->prec == 0 && pf->sharp == 0))
	{
		if (pf->len == 1)
			ft_printnbr((unsigned char)pf->u, 8, pf);
		else if (pf->len == 2)
			ft_printnbr((unsigned short)pf->u, 8, pf);
		else
			ft_printnbr(pf->u, 8, pf);
	}
	ft_post_numflags(pf->u, 8, pf);
}

void		ft_print_oup(t_pf *pf)
{
	pf->u = va_arg(pf->argp, unsigned long);
	ft_pre_unumflags(pf->u, 8, pf);
	if (!(pf->u == 0 && pf->dot == 1 && pf->prec == 0 && pf->sharp == 0))
		ft_printnbr(pf->u, 8, pf);
	ft_post_numflags(pf->u, 8, pf);
}

void		ft_print_x(t_pf *pf)
{
	if (pf->len == 3)
		pf->u = va_arg(pf->argp, unsigned long);
	else if (pf->len == 4 || pf->len == 7)
		pf->u = va_arg(pf->argp, unsigned long long);
	else if (pf->len == 5)
		pf->u = va_arg(pf->argp, uintmax_t);
	else if (pf->len == 6)
		pf->u = va_arg(pf->argp, size_t);
	else
		pf->u = va_arg(pf->argp, unsigned int);
	ft_pre_unumflags(pf->u, 16, pf);
	if (!(pf->u == 0 && pf->dot == 1 && pf->prec == 0))
	{
		if (pf->len == 1)
			ft_printnbr((unsigned char)pf->u, 16, pf);
		else if (pf->len == 2)
			ft_printnbr((unsigned short)pf->u, 16, pf);
		else
			ft_printnbr(pf->u, 16, pf);
	}
	ft_post_numflags(pf->u, 16, pf);
}

void		ft_print_xup(t_pf *pf)
{
	pf->maj = 1;
	if (pf->len == 3)
		pf->u = va_arg(pf->argp, unsigned long);
	else if (pf->len == 4 || pf->len == 7)
		pf->u = va_arg(pf->argp, unsigned long long);
	else if (pf->len == 5)
		pf->u = va_arg(pf->argp, uintmax_t);
	else if (pf->len == 6)
		pf->u = va_arg(pf->argp, size_t);
	else
		pf->u = va_arg(pf->argp, unsigned int);
	ft_pre_unumflags(pf->u, 16, pf);
	if (!(pf->u == 0 && pf->dot == 1 && pf->prec == 0))
	{
		if (pf->len == 1)
			ft_printnbr((unsigned char)pf->u, 16, pf);
		else if (pf->len == 2)
			ft_printnbr((unsigned short)pf->u, 16, pf);
		else
			ft_printnbr(pf->u, 16, pf);
	}
	ft_post_numflags(pf->u, 16, pf);
}

void		ft_print_f(t_pf *pf)
{
	if (pf->dot == 0)
		pf->prec = 6;
	if (pf->len == 7)
	{
		pf->f = va_arg(pf->argp, long double);
		pf->f = ft_ldtold(pf->f, pf);
	}
	else
	{
		pf->f = va_arg(pf->argp, double);
		pf->f = ft_dtold(pf->f, pf);
	}
	ft_pre_floatflags(pf->f, pf);
	if (!(pf->f == 0 && pf->dot == 1 && pf->prec == 0))
		ft_printfloat(pf->f, pf);
	ft_post_floatflags(pf->f, pf);
}

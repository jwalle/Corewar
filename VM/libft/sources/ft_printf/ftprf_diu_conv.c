/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diu_conv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmicolon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 19:26:54 by rmicolon          #+#    #+#             */
/*   Updated: 2016/03/15 20:44:30 by rmicolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_print_di(t_pf *pf)
{
	if (pf->len == 3)
		pf->i = va_arg(pf->argp, long);
	else if (pf->len == 4 || pf->len >= 6)
		pf->i = va_arg(pf->argp, long long);
	else if (pf->len == 5)
		pf->i = va_arg(pf->argp, intmax_t);
	else
		pf->i = va_arg(pf->argp, int);
	if (pf->len == 1)
		pf->i = ft_stou((signed char)pf->i, pf);
	else if (pf->len == 2)
		pf->i = ft_stou((short)pf->i, pf);
	else
		pf->i = ft_stou(pf->i, pf);
	ft_pre_numflags(pf->i, 10, pf);
	if (!(pf->i == 0 && pf->dot == 1 && pf->prec == 0))
		ft_printnbr(pf->i, 10, pf);
	ft_post_numflags(pf->i, 10, pf);
}

void		ft_print_dup(t_pf *pf)
{
	pf->i = va_arg(pf->argp, long);
	pf->i = ft_stou(pf->i, pf);
	ft_pre_numflags(pf->i, 10, pf);
	if (!(pf->i == 0 && pf->dot == 1 && pf->prec == 0))
		ft_printnbr(pf->i, 10, pf);
	ft_post_numflags(pf->i, 10, pf);
}

void		ft_print_u(t_pf *pf)
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
	ft_pre_unumflags(pf->u, 10, pf);
	if (!(pf->u == 0 && pf->dot == 1 && pf->prec == 0))
	{
		if (pf->len == 1)
			ft_printnbr((unsigned char)pf->u, 10, pf);
		else if (pf->len == 2)
			ft_printnbr((unsigned short)pf->u, 10, pf);
		else
			ft_printnbr(pf->u, 10, pf);
	}
	ft_post_numflags(pf->u, 10, pf);
}

void		ft_print_uup(t_pf *pf)
{
	pf->u = va_arg(pf->argp, unsigned long);
	ft_pre_unumflags(pf->u, 10, pf);
	if (!(pf->u == 0 && pf->dot == 1 && pf->prec == 0))
		ft_printnbr(pf->u, 10, pf);
	ft_post_numflags(pf->u, 10, pf);
}

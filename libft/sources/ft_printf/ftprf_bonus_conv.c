/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_conv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmicolon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 19:26:37 by rmicolon          #+#    #+#             */
/*   Updated: 2016/03/15 20:43:35 by rmicolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_print_b(t_pf *pf)
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
	ft_pre_unumflags(pf->u, 2, pf);
	if (!(pf->u == 0 && pf->dot == 1 && pf->prec == 0 && pf->sharp == 0))
	{
		if (pf->len == 1)
			ft_printnbr((unsigned char)pf->u, 2, pf);
		else if (pf->len == 2)
			ft_printnbr((unsigned short)pf->u, 2, pf);
		else
			ft_printnbr(pf->u, 2, pf);
	}
	ft_post_numflags(pf->u, 2, pf);
}

void		ft_print_m(t_pf *pf)
{
	pf->u = va_arg(pf->argp, unsigned long long);
	print_memory(&pf->u, sizeof(&pf->u));
	pf->ret += 49;
}

void		ft_print_n(t_pf *pf)
{
	pf->n = va_arg(pf->argp, int *);
	*pf->n = pf->ret;
}

void		ft_print_percent(t_pf *pf)
{
	pf->i = '%';
	ft_pre_charflags(pf);
	ft_printchar(pf->i, pf);
	ft_post_charflags(pf);
}

void		ft_set_fd(t_pf *pf)
{
	pf->fd = va_arg(pf->argp, int);
	struct_reset(pf);
}

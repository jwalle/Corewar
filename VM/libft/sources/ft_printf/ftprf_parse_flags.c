/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmicolon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 19:25:08 by rmicolon          #+#    #+#             */
/*   Updated: 2016/03/16 00:33:03 by rmicolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_flags(t_pf *pf)
{
	if (*pf->fmt == '#')
		pf->sharp = 1;
	else if (*pf->fmt == '0')
	{
		if (pf->minus == 0)
			pf->zero = 1;
	}
	else if (*pf->fmt == '-')
	{
		pf->minus = 1;
		pf->zero = 0;
	}
	else if (*pf->fmt == '+')
		pf->plus = 1;
	else if (*pf->fmt == ' ')
		pf->space = 1;
	else if (*pf->fmt == '\'')
		pf->ts = 1;
}

void		ft_width(t_pf *pf)
{
	if (*pf->fmt == '*')
	{
		pf->width = va_arg(pf->argp, int);
		if (pf->width < 0)
		{
			pf->zero = 0;
			pf->minus = 1;
			pf->width *= -1;
		}
	}
	else if (*pf->fmt >= '1' && *pf->fmt <= '9')
	{
		pf->width = *pf->fmt - 48;
		while (*(pf->fmt + 1) >= '0' && *(pf->fmt + 1) <= '9')
		{
			pf->width = (10 * pf->width) + *(pf->fmt + 1) - 48;
			pf->fmt++;
		}
		pf->brk = 1;
	}
}

void		ft_precision(t_pf *pf)
{
	if (*pf->fmt == '.')
	{
		pf->dot = 1;
		if (*(pf->fmt + 1) == '*')
		{
			pf->prec = va_arg(pf->argp, int);
			if (pf->prec < 0)
			{
				pf->dot = 0;
				pf->prec = 0;
			}
			pf->fmt++;
		}
		else
		{
			if (*(pf->fmt + 1) >= '0' && *(pf->fmt + 1) <= '9')
				while (*(pf->fmt + 1) >= '0' && *(pf->fmt + 1) <= '9')
					pf->prec = (10 * pf->prec) + *(++pf->fmt) - 48;
			else
				pf->prec = 0;
		}
		pf->brk = 1;
	}
}

void		ft_lenght(t_pf *pf)
{
	if (pf->len < 1 && *pf->fmt == 'h')
	{
		if (*(pf->fmt + 1) == 'h')
		{
			pf->len = 1;
			pf->fmt++;
		}
		else
			pf->len = 2;
	}
	else if (pf->len < 3 && *pf->fmt == 'l')
	{
		if (*(pf->fmt + 1) == 'l')
		{
			pf->len = 4;
			pf->fmt++;
		}
		else
			pf->len = 3;
	}
	else if (pf->len < 5 && (*pf->fmt == 'j' || *pf->fmt == 'z'))
		pf->len = (*pf->fmt == 'j') ? 5 : 6;
	else if (pf->len == 0 && *pf->fmt == 'L')
		pf->len = 7;
}

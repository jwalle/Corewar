/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_alphaflags.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmicolon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 19:25:21 by rmicolon          #+#    #+#             */
/*   Updated: 2016/03/15 22:46:06 by rmicolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_pre_strflags(char *str, t_pf *pf)
{
	if (pf->width > 0 && pf->minus == 0)
		ft_print_strwidth(str, pf);
}

void		ft_pre_wstrflags(wchar_t *str, t_pf *pf)
{
	if (pf->width > 0 && pf->minus == 0)
		ft_print_wstrwidth(str, pf);
}

void		ft_pre_charflags(t_pf *pf)
{
	if (pf->width > 0 && pf->minus == 0)
		ft_print_charwidth(pf);
}

void		ft_pre_wcharflags(wchar_t c, t_pf *pf)
{
	int	tsize;

	if (pf->width > 0 && pf->minus == 0)
	{
		tsize = ft_bitsize(c);
		if (tsize < 8)
			tsize = 1;
		else if (tsize < 12)
			tsize = 2;
		else if (tsize < 17)
			tsize = 3;
		else
			tsize = 4;
		while (tsize < pf->width)
		{
			if (pf->zero == 1)
				ft_printchar('0', pf);
			else
				ft_printchar(' ', pf);
			tsize++;
		}
	}
}

void		ft_post_wcharflags(wchar_t c, t_pf *pf)
{
	int	tsize;

	if (pf->width > 0 && pf->minus == 1)
	{
		tsize = ft_bitsize(c);
		if (tsize < 8)
			tsize = 1;
		else if (tsize < 12)
			tsize = 2;
		else if (tsize < 17)
			tsize = 3;
		else
			tsize = 4;
		while (tsize < pf->width)
		{
			if (pf->zero == 1)
				ft_printchar('0', pf);
			else
				ft_printchar(' ', pf);
			tsize++;
		}
	}
}

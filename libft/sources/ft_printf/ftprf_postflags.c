/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   postflags.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmicolon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 19:25:14 by rmicolon          #+#    #+#             */
/*   Updated: 2016/03/15 21:58:46 by rmicolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_post_strflags(char *str, t_pf *pf)
{
	if (pf->width > 0 && pf->minus == 1)
		ft_print_strwidth(str, pf);
	struct_reset(pf);
}

void		ft_post_wstrflags(wchar_t *str, t_pf *pf)
{
	if (pf->width > 0 && pf->minus == 1)
		ft_print_wstrwidth(str, pf);
	struct_reset(pf);
}

void		ft_post_charflags(t_pf *pf)
{
	if (pf->width > 0 && pf->minus == 1)
		ft_print_charwidth(pf);
	struct_reset(pf);
}

void		ft_post_numflags(unsigned long long int nb, char base, t_pf *pf)
{
	if (pf->width > 0 && pf->minus == 1 && pf->zero == 0)
		ft_print_numwidth(nb, base, pf);
	struct_reset(pf);
}

void		ft_post_floatflags(long double nb, t_pf *pf)
{
	if (pf->width > 0 && pf->minus == 1 && pf->zero == 0)
		ft_print_numwidth(nb, 10, pf);
	struct_reset(pf);
}

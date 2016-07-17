/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmicolon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 19:26:19 by rmicolon          #+#    #+#             */
/*   Updated: 2016/03/16 00:47:56 by rmicolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		struct_reset(t_pf *pf)
{
	pf->i = 0;
	pf->u = 0;
	pf->f = 0.0;
	pf->lc = 0;
	pf->s = NULL;
	pf->ls = NULL;
	pf->n = NULL;
	pf->maj = 0;
	pf->brk = 0;
	pf->len = 0;
	pf->dot = 0;
	pf->prec = 0;
	pf->ts = 0;
	pf->tsc = 0;
	pf->nsize = 1;
	pf->width = 0;
	pf->sharp = 0;
	pf->zero = 0;
	pf->minus = 0;
	pf->plus = 0;
	pf->space = 0;
	pf->neg = 0;
}

int			ft_bitsize(unsigned int nbr)
{
	int	power;

	power = 0;
	while (nbr)
	{
		nbr = nbr >> 1;
		power++;
	}
	return (power);
}

void		ft_print_prefix(char *str, t_pf *pf)
{
	while (str && *str)
	{
		ft_printchar(*str, pf);
		str++;
	}
}

int			ft_wwidthlen(wchar_t *str)
{
	int	i;
	int	j;
	int	size;

	i = 0;
	j = 0;
	size = 0;
	while (str && str[j])
	{
		size = ft_bitsize(str[j]);
		if (size < 8)
			i += 1;
		else if (size < 12)
			i += 2;
		else if (size < 17)
			i += 3;
		else
			i += 4;
		j++;
	}
	return (i);
}

int			ft_wideprec(wchar_t *str, t_pf *pf)
{
	int	i;
	int	size;
	int	count;
	int	print;

	i = 0;
	size = 0;
	count = 0;
	print = 0;
	while (str[i] && print + count <= pf->prec)
	{
		print += count;
		size = ft_bitsize(str[i++]);
		if (size < 8)
			count = 1;
		else if (size < 12)
			count = 2;
		else if (size < 17)
			count = 3;
		else
			count = 4;
	}
	return (print);
}

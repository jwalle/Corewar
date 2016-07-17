/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmicolon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/08 16:20:02 by rmicolon          #+#    #+#             */
/*   Updated: 2016/03/22 00:30:07 by rmicolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		ft_proceed(t_pf *pf, t_fptr *fconv, t_fptr *fpre, int i)
{
	if (pf->fmt && *pf->fmt && fconv && fpre)
	{
		while (i < 4 && pf->brk == 0)
			fpre[i++].ptr(pf);
		pf->brk = 0;
		if (!ft_strchr(pf->chr, *pf->fmt))
		{
			i = 0;
			while (fconv[i].op != *pf->fmt && fconv[i].op != 0)
				i++;
			if (fconv[i].op != 0)
			{
				fconv[i].ptr(pf);
				return (0);
			}
			ft_print_bad_conv(pf);
			return (0);
		}
		if (*(pf->fmt + 1))
		{
			pf->fmt++;
			ft_proceed(pf, fconv, fpre, 0);
		}
	}
	return (0);
}

static void		scan(t_pf *pf, t_fptr *fconv, t_fptr *fpre)
{
	int	len;

	len = 0;
	while (*pf->fmt)
	{
		if (*pf->fmt == '%')
		{
			if (*(pf->fmt + 1))
			{
				pf->fmt++;
				ft_proceed(pf, fconv, fpre, 0);
			}
		}
		else
			ft_printchar(*pf->fmt, pf);
		++pf->fmt;
	}
}

int				ft_printf(const char *restrict format, ...)
{
	t_pf		*pf;
	t_fptr		fconv[22];
	t_fptr		fpre[5];
	int			ret;

	pf = NULL;
	if (!(pf = (t_pf *)malloc(sizeof(*pf))))
		return (-1);
	struct_init(pf, format);
	fconv_init(fconv);
	fpre_init(fpre);
	va_start(pf->argp, format);
	scan(pf, fconv, fpre);
	va_end(pf->argp);
	ret = pf->ret;
	free(pf);
	return (ret);
}

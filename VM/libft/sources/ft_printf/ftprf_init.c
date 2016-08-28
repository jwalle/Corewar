/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmicolon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 19:24:56 by rmicolon          #+#    #+#             */
/*   Updated: 2016/03/22 00:37:10 by rmicolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_fptr	tab_init(char op, void (*ptr)(t_pf*))
{
	t_fptr fptr;

	fptr.op = op;
	fptr.ptr = ptr;
	return (fptr);
}

void			fconv_init(t_fptr *fptr)
{
	fptr[0] = tab_init('d', ft_print_di);
	fptr[1] = tab_init('D', ft_print_dup);
	fptr[2] = tab_init('i', ft_print_di);
	fptr[3] = tab_init('o', ft_print_o);
	fptr[4] = tab_init('O', ft_print_oup);
	fptr[5] = tab_init('u', ft_print_u);
	fptr[6] = tab_init('U', ft_print_uup);
	fptr[7] = tab_init('x', ft_print_x);
	fptr[8] = tab_init('X', ft_print_xup);
	fptr[9] = tab_init('c', ft_print_c);
	fptr[10] = tab_init('C', ft_print_cup);
	fptr[11] = tab_init('s', ft_print_s);
	fptr[12] = tab_init('S', ft_print_sup);
	fptr[13] = tab_init('p', ft_print_p);
	fptr[14] = tab_init('f', ft_print_f);
	fptr[15] = tab_init('F', ft_print_f);
	fptr[16] = tab_init('b', ft_print_b);
	fptr[17] = tab_init('m', ft_print_m);
	fptr[18] = tab_init('n', ft_print_n);
	fptr[19] = tab_init('%', ft_print_percent);
	fptr[20] = tab_init('!', ft_set_fd);
	fptr[21] = tab_init(0, NULL);
}

void			fpre_init(t_fptr *fptr)
{
	fptr[0] = tab_init(0, ft_precision);
	fptr[1] = tab_init(1, ft_width);
	fptr[2] = tab_init(2, ft_flags);
	fptr[3] = tab_init(3, ft_lenght);
	fptr[4] = tab_init(4, NULL);
}

static void		struct_init2(t_pf *pf)
{
	pf->prec = 0;
	pf->width = 0;
	pf->sharp = 0;
	pf->zero = 0;
	pf->minus = 0;
	pf->plus = 0;
	pf->space = 0;
	pf->neg = 0;
	pf->ts = 0;
	pf->tsc = 0;
	pf->nsize = 1;
	pf->mask[0] = 49280;
	pf->mask[1] = 14712960;
	pf->mask[2] = 4034953344;
	pf->chr = "jzlhL.#-+ *'0123456789";
}

void			struct_init(t_pf *pf, const char *restrict format)
{
	pf->fd = 1;
	pf->i = 0;
	pf->u = 0;
	pf->f = 0.0;
	pf->lc = 0;
	pf->s = NULL;
	pf->ls = NULL;
	pf->n = NULL;
	pf->fmt = format;
	pf->maj = 0;
	pf->ret = 0;
	pf->brk = 0;
	pf->len = 0;
	pf->dot = 0;
	struct_init2(pf);
}

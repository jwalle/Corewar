/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmicolon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 19:25:54 by rmicolon          #+#    #+#             */
/*   Updated: 2016/03/14 19:44:22 by rmicolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		ft_print_w4(unsigned int value, t_pf *pf)
{
	unsigned char	octet;
	unsigned char	o1;
	unsigned char	o2;
	unsigned char	o3;
	unsigned char	o4;

	o1 = (value << 26) >> 26;
	o2 = ((value >> 6) << 26) >> 26;
	o3 = ((value >> 12) << 26) >> 26;
	o4 = ((value >> 18) << 29) >> 29;
	octet = (pf->mask[2] >> 24) | o4;
	write(pf->fd, &octet, 1);
	octet = ((pf->mask[2] << 8) >> 24) | o3;
	write(pf->fd, &octet, 1);
	octet = ((pf->mask[2] << 16) >> 24) | o2;
	write(pf->fd, &octet, 1);
	octet = ((pf->mask[2] << 24) >> 24) | o1;
	write(pf->fd, &octet, 1);
	pf->ret += 4;
}

static void		ft_print_w3(unsigned int value, t_pf *pf)
{
	unsigned char	octet;
	unsigned char	o1;
	unsigned char	o2;
	unsigned char	o3;

	o1 = (value << 26) >> 26;
	o2 = ((value >> 6) << 26) >> 26;
	o3 = ((value >> 12) << 28) >> 28;
	octet = (pf->mask[1] >> 16) | o3;
	write(pf->fd, &octet, 1);
	octet = ((pf->mask[1] << 16) >> 24) | o2;
	write(pf->fd, &octet, 1);
	octet = ((pf->mask[1] << 24) >> 24) | o1;
	write(pf->fd, &octet, 1);
	pf->ret += 3;
}

void			ft_printit(wchar_t c, unsigned int value, int s, t_pf *pf)
{
	unsigned char	octet;
	unsigned char	o1;
	unsigned char	o2;

	if (s < 8)
	{
		octet = c;
		write(pf->fd, &octet, 1);
		pf->ret++;
	}
	else if (s < 12)
	{
		o1 = (value << 26) >> 26;
		o2 = ((value >> 6) << 27) >> 27;
		octet = (pf->mask[0] >> 8) | o2;
		write(pf->fd, &octet, 1);
		octet = ((pf->mask[0] << 24) >> 24) | o1;
		write(pf->fd, &octet, 1);
		pf->ret += 2;
	}
	else if (s < 17)
		ft_print_w3(value, pf);
	else
		ft_print_w4(value, pf);
}

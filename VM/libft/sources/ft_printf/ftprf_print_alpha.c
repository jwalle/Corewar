/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_alpha.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmicolon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 19:25:35 by rmicolon          #+#    #+#             */
/*   Updated: 2016/03/22 00:03:18 by rmicolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_printchar(char c, t_pf *pf)
{
	write(pf->fd, &c, 1);
	pf->ret++;
}

void		ft_printwchar(wchar_t c, t_pf *pf)
{
	unsigned int	value;
	int				size;

	value = c;
	size = ft_bitsize(c);
	ft_printit(c, value, size, pf);
}

void		ft_printstr(char *str, t_pf *pf)
{
	int		i;
	int		len;
	int		retsf;

	i = 0;
	retsf = pf->ret;
	len = ft_strlen(str);
	if (pf->dot == 0)
	{
		write(pf->fd, str, len);
		pf->ret += len;
	}
	else
	{
		while (str[i])
		{
			if (pf->prec > 0)
				ft_printchar(str[i++], pf);
			if ((pf->ret - retsf) + 1 > pf->prec)
				break ;
		}
	}
}

void		ft_printwstr(wchar_t *str, t_pf *pf)
{
	int		i;
	int		retsf;
	int		size;
	int		count;

	i = 0;
	retsf = pf->ret;
	while (str[i])
	{
		if (pf->dot == 1)
		{
			size = ft_bitsize(str[i]);
			count = 4;
			if (size < 8)
				count -= 3;
			else if (size < 12)
				count -= 2;
			else if (size < 17)
				count -= 1;
			if ((pf->ret - retsf) + count > pf->prec)
				break ;
		}
		ft_printwchar(str[i++], pf);
	}
}

void		ft_print_bad_conv(t_pf *pf)
{
	ft_pre_charflags(pf);
	ft_printchar(*pf->fmt, pf);
	ft_post_charflags(pf);
}

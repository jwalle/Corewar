/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_misc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/05 05:00:16 by jwalle            #+#    #+#             */
/*   Updated: 2016/08/05 05:00:25 by jwalle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

unsigned int	cw_betole(unsigned int a)
{
	unsigned int	b;
	unsigned char	*src;
	unsigned char	*dst;

	src = (unsigned char *)&a;
	dst = (unsigned char *)&b;
	dst[0] = src[3];
	dst[1] = src[2];
	dst[2] = src[1];
	dst[3] = src[0];
	return (b);
}

int				circ(int index, int add)
{
	int		i;

	i = (index + add) % MEM_SIZE;
	return (i >= 0 ? i : i + MEM_SIZE);
}

void			cw_dump_mem(t_cwar *cwar)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (cwar->arena)
	{
		while (i < MEM_SIZE)
		{
			if (!j)
			{
				ft_printf("0x0000 : ");
				j++;
			}
			if (i && ((i) % 64) == 0)
				ft_printf("%#.4x : ", j++ * 64);
			ft_printf("%.2x ", cwar->arena[i]);
			if (((i + 1) % 64) == 0)
				ft_putchar('\n');
			++i;
		}
	}
	exit(1);
}

int				is_number(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int				check_if_id_available(t_cwar *cwar, int n)
{
	t_player	*cur;

	cur = cwar->players;
	while (cur)
	{
		if (cur->id == n)
			return (check_if_id_available(cwar, ++n));
		cur = cur->next;
	}
	return (n);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmicolon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/30 17:07:42 by rmicolon          #+#    #+#             */
/*   Updated: 2016/03/04 16:16:48 by rmicolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_put_base_nbr(int n)
{
	char	c;

	if (n >= 16)
	{
		ft_put_base_nbr(n / 16);
		ft_put_base_nbr(n % 16);
	}
	else
	{
		if (n <= 9)
			c = n + '0';
		else
			c = (n - 10) + 'a';
		write(1, &c, 1);
	}
}

static void		proceed(char *buff, unsigned char *pc, size_t i)
{
	size_t j;

	if ((i % 16) == 0 && i != 0)
	{
		ft_putstr(buff);
		ft_putstr("\n");
		j = 0;
		while (buff[j + 1])
			buff[j++] = '\0';
	}
	if (pc[i] < 16)
		ft_put_base_nbr(0);
	ft_put_base_nbr(pc[i]);
	if ((i % 2) == 1)
		write(1, " ", 1);
	if (pc[i] < 32 || pc[i] > 126)
		buff[i % 16] = '.';
	else
		buff[i % 16] = pc[i];
	buff[(i % 16) + 1] = '\0';
}

void			print_memory(const void *addr, size_t size)
{
	size_t			i;
	char			buff[17];
	unsigned char	*pc;

	i = 0;
	pc = (unsigned char *)addr;
	while (i < size)
	{
		proceed(buff, pc, i);
		i++;
	}
	while ((i % 16) != 0)
	{
		if ((i % 2) == 1)
			write(1, " ", 1);
		write(1, "  ", 2);
		i++;
	}
	ft_putstr(buff);
	ft_putstr("\n");
}

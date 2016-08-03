/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ins_tools_one.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/03 19:03:16 by jwalle            #+#    #+#             */
/*   Updated: 2016/08/03 19:03:27 by jwalle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		get_dir(t_cwar *cwar, int cur)
{
	int	i;
	int	index;

	i = 1;
	index = 0;
	while (i <= DIR_SIZE)
	{
		index <<= 8;
		index += cwar->arena[circ(cur, i)];
		++i;
	}
	return (index);
}

int		get_ind(t_cwar *cwar, t_proc *proc, int cur)
{
	int	i;
	int	index;
	int	adress;

	i = 1;
	index = 0;
	adress = 0;
	while (i <= IND_SIZE)
	{
		adress <<= 8;
		adress += cwar->arena[circ(cur, i)];
		++i;
	}
	adress = (short)adress % IDX_MOD;
	i = 0;
	while (i < REG_SIZE)
	{
		index <<= 8;
		index += cwar->arena[circ(proc->pc, adress + i++)];
	}
	return (index);
}

int		get_reg(t_cwar *cwar, t_proc *proc, int cur)
{
	int	index;
	int	i;

	index = 0;
	if (cwar->arena[circ(cur, 1)] && cwar->arena[circ(cur, 1)] <= REG_NUMBER)
	{
		i = 0;
		while (i < REG_SIZE)
		{
			index <<= 8;
			index += proc->reg[cwar->arena[circ(cur, 1)]][i];
			++i;
		}
	}
	return (index);
}

char	put_in_reg(t_proc *proc, int index, unsigned char regnum)
{
	int i;
	int	carry;

	if (regnum && regnum <= REG_NUMBER)
	{
		carry = (index == 0) ? 1 : 0;
		i = REG_SIZE - 1;
		while (i >= 0 && index)
		{
			proc->reg[regnum][i] = index;
			index = index >> 8;
			--i;
		}
		return (carry);
	}
	return (proc->carry);
}

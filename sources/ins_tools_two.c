/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ins_tools_two.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmicolon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/04 23:30:21 by rmicolon          #+#    #+#             */
/*   Updated: 2016/08/04 23:31:41 by rmicolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

char	cw_fillreg(t_cwar *cwar, t_proc *proc, unsigned char regnum, int index)
{
	int i;
	int	carry;

	carry = 0;
	if (regnum && regnum <= REG_NUMBER)
	{
		i = 0;
		while (i < REG_SIZE)
		{
			carry <<= 8;
			proc->reg[regnum][i++] = cwar->arena[index];
			carry += cwar->arena[index];
			index = circ(index, 1);
		}
		return (carry == 0) ? 1 : 0;
	}
	return (proc->carry);
}

void	cw_regcpy(t_proc *proc, unsigned char regn1, unsigned char regn2)
{
	int	i;

	if (regn1 && regn1 <= REG_NUMBER && regn2 && regn2 <= REG_NUMBER)
	{
		i = 0;
		while (i < REG_SIZE)
		{
			proc->reg[regn2][i] = proc->reg[regn2][i];
			++i;
		}
	}
}

void	cw_regongrid(t_cwar *cwar, unsigned char *reg, int index, t_proc *proc)
{
	int	i;

	i = 0;
	while (i < REG_SIZE)
	{
		cwar->arena_color[circ(index, i)][0] = (proc->player_id % 4) + 1;
		cwar->arena[circ(index, i)] = reg[i];
		++i;
	}
}

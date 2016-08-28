/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ins_tools_two.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmicolon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/04 23:30:21 by rmicolon          #+#    #+#             */
/*   Updated: 2016/08/05 01:03:20 by rmicolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

char	cw_fillreg(t_cwar *cwar, t_proc *proc, unsigned char regnum, int i)
{
	int j;
	int	carry;

	carry = 0;
	if (regnum && regnum <= REG_NUMBER)
	{
		j = 0;
		while (j < REG_SIZE)
		{
			carry <<= 8;
			proc->reg[regnum][j++] = cwar->arena[i];
			carry += cwar->arena[i];
			i = circ(i, 1);
		}
		return (carry == 0) ? 1 : 0;
	}
	return (proc->carry);
}

void	cw_regcpy(t_proc *proc, unsigned char regn1, unsigned char regn2)
{
	int	j;

	if (regn1 && regn1 <= REG_NUMBER && regn2 && regn2 <= REG_NUMBER)
	{
		j = 0;
		while (j < REG_SIZE)
		{
			proc->reg[regn2][j] = proc->reg[regn1][j];
			++j;
		}
	}
}

void	cw_regongrid(t_cwar *cwar, unsigned char *reg, int i, t_proc *proc)
{
	int	j;

	j = 0;
	while (j < REG_SIZE)
	{
		cwar->arena_color[circ(i, j)][0] = (proc->player_id % 4) + 1;
		cwar->arena[circ(i, j)] = reg[j];
		++j;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmicolon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/24 19:04:54 by rmicolon          #+#    #+#             */
/*   Updated: 2016/07/25 17:42:22 by rmicolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		cw_updatepc(int pc, int cbyte)
{
	pc += 2;
	while (cbyte)
	{
		if ((cbyte & 3) == 1)
			pc++;
		else if ((cbyte & 3) == 2)
			pc += REG_SIZE;
		else if ((cbyte & 3) == 3)
			pc += IND_SIZE;
		cbyte >>= 2;
	}
	return (pc);
}

void	cw_fillreg(t_cwar *cwar, t_proc *proc, unsigned char regnum, int index)
{
	int i;

	if (regnum && regnum <= REG_NUMBER)
	{
		i = 0;
		while (i < REG_SIZE)
			proc->reg[regnum][i++] = cwar->arena[index++];
	}
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
		cwar->arena_color[index + i][0] = proc->player_id;
		cwar->arena[index + i] = reg[i];
		++i;
	}
}

void	cw_load(t_cwar *cwar, t_proc *proc)
{
	int				i;
	unsigned char	cbyte;
	int				cur;
	int				index;

	cur = proc->pc + 1;
	cbyte = cwar->arena[cur];
	if (((cbyte >> 6) & 3) == 3)
	{
		i = 1;
		index = 0;
		while (i <= IND_SIZE)
		{
			index <<= 8;
			index += cwar->arena[cur + i++]; // TODO CIRCULAIRE
		}
		cw_fillreg(cwar, proc, cwar->arena[cur + IND_SIZE + 1], proc->pc + index);
	}
	else if (((cbyte >> 6) & 3) == 2)
		cw_fillreg(cwar, proc, cwar->arena[cur + REG_SIZE + 1], cur + 1);
	proc->pc = cw_updatepc(proc->pc, cbyte);
}

void	cw_store(t_cwar *cwar, t_proc *proc)
{
	int				cur;
	int				i;
	unsigned char	cbyte;
	int				index;

	cur = proc->pc + 1;
	cbyte = cwar->arena[cur];
	if (cwar->arena[cur + 1] && cwar->arena[cur + 1] <= REG_NUMBER)
	{
		if (((cbyte >> 4) & 3) == 1)
			cw_regcpy(proc, cwar->arena[cur + 1], cwar->arena[cur + 2]);
		if (((cbyte >> 4) & 3) == 3)
		{
			i = 1;
			index = 0;
			while (i <= IND_SIZE)
			{
				index <<= 8;
				index += cwar->arena[cur + 1 + i++];
			}
			cw_regongrid(cwar, proc->reg[cwar->arena[cur + 1]], proc->pc + index, proc);
		}
	}
	proc->pc = cw_updatepc(proc->pc, cbyte);
}

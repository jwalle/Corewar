/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loads.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmicolon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/04 23:35:41 by rmicolon          #+#    #+#             */
/*   Updated: 2016/08/04 23:36:41 by rmicolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	cw_load(t_cwar *cwar, t_proc *proc)
{
	int				i;
	unsigned char	cbyte;
	int				cur;
	int				index;

	cur = circ(proc->pc, 1);
	cbyte = cwar->arena[cur];
	if (((cbyte >> 6) & 3) == 3)
	{
		i = 1;
		index = 0;
		while (i <= IND_SIZE)
		{
			index <<= 8;
			index += cwar->arena[circ(cur, i)];
			i = circ(i, 1);
		}
		proc->carry = cw_fillreg(cwar, proc, cwar->arena[circ(cur,
				IND_SIZE + 1)], circ(proc->pc, (index % IDX_MOD)));
	}
	else if (((cbyte >> 6) & 3) == 2)
		proc->carry = cw_fillreg(cwar, proc,
			cwar->arena[circ(cur, REG_SIZE + 1)], circ(cur, 1));
	proc->pc = cw_updatepc(proc->pc, cbyte);
}

int		cw_ldi2(t_cwar *cwar, t_proc *proc, int *cur, int cbyte)
{
	int	index;

	index = 0;
	if (((cbyte >> 6) & 3) == 1)
	{
		index = get_reg(cwar, proc, *cur);
		*cur = circ(*cur, 1);
	}
	else if (((cbyte >> 6) & 3) == 2)
	{
		index = get_sdir(cwar, *cur);
		*cur = circ(*cur, 2);
	}
	else if (((cbyte >> 6) & 3) == 3)
	{
		index = get_ind(cwar, proc, *cur);
		*cur = circ(*cur, 2);
	}
	return (index);
}

void	cw_loadindex(t_cwar *cwar, t_proc *proc)
{
	unsigned char	cbyte;
	int				cur;
	int				adress;

	cur = circ(proc->pc, 1);
	cbyte = cwar->arena[cur];
	adress = cw_ldi2(cwar, proc, &cur, cbyte);
	if (((cbyte >> 4) & 3) == 1)
	{
		adress += get_reg(cwar, proc, cur);
		cur = circ(cur, 2);
	}
	else if (((cbyte >> 4) & 3) == 2)
	{
		adress += get_sdir(cwar, cur);
		cur = circ(cur, 3);
	}
	if (cwar->arena[cur] && cwar->arena[cur] <= REG_NUMBER)
		cw_fillreg(cwar, proc, cwar->arena[cur],
			circ(proc->pc, (adress % IDX_MOD)));
	proc->pc = cw_updatestipc(proc->pc, cbyte);
}

void	cw_longload(t_cwar *cwar, t_proc *proc)
{
	int				i;
	unsigned char	cbyte;
	int				cur;
	int				index;

	cur = circ(proc->pc, 1);
	cbyte = cwar->arena[cur];
	if (((cbyte >> 6) & 3) == 3)
	{
		i = 1;
		index = 0;
		while (i <= IND_SIZE)
		{
			index <<= 8;
			index += cwar->arena[circ(cur, i)];
			i = circ(i, 1);
		}
		proc->carry = cw_fillreg(cwar, proc, cwar->arena[
			circ(cur, IND_SIZE + 1)], circ(proc->pc, index));
	}
	else if (((cbyte >> 6) & 3) == 2)
		proc->carry = cw_fillreg(cwar, proc, cwar->arena[
			circ(cur, REG_SIZE + 1)], circ(cur, 1));
	proc->pc = cw_updatepc(proc->pc, cbyte);
}

void	cw_longloadindex(t_cwar *cwar, t_proc *proc)
{
	unsigned char	cbyte;
	int				cur;
	int				adress;

	cur = circ(proc->pc, 1);
	cbyte = cwar->arena[cur];
	adress = cw_ldi2(cwar, proc, &cur, cbyte);
	if (((cbyte >> 4) & 3) == 1)
	{
		adress += get_reg(cwar, proc, cur);
		cur = circ(cur, 2);
	}
	else if (((cbyte >> 4) & 3) == 2)
	{
		adress += get_sdir(cwar, cur);
		cur = circ(cur, 3);
	}
	if (cwar->arena[cur] && cwar->arena[cur] <= REG_NUMBER)
		proc->carry = cw_fillreg(cwar, proc, cwar->arena[cur],
			circ(proc->pc, adress));
	proc->pc = cw_updatestipc(proc->pc, cbyte);
}

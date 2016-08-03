/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or_and_xor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/28 20:39:37 by jwalle            #+#    #+#             */
/*   Updated: 2016/08/03 04:22:14 by rmicolon         ###   ########.fr       */
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

/*
** IND_SIZE = 2
** DIR_SIZE = REG_SIZE = 4
*/

int		cw_solo_updatepc(int pc, int cbyte)
{
	if ((cbyte & 3) == 1)
		pc = circ(pc, 1);
	else if ((cbyte & 3) == 2)
		pc = circ(pc, DIR_SIZE);
	else if ((cbyte & 3) == 3)
		pc = circ(pc, IND_SIZE);
	return (pc);
}

void	cw_and(t_cwar *cwar, t_proc *proc)
{
	int	cbyte;
	int	index;
	int	cur;

	cur = circ(proc->pc, 1);
	cbyte = cwar->arena[cur];
	index = 0;
	if (((cbyte >> 6) & 3) == 1)
		index = get_reg(cwar, proc, cur);
	else if (((cbyte >> 6) & 3) == 2)
		index = get_dir(cwar, cur);
	else if (((cbyte >> 6) & 3) == 3)
		index = get_ind(cwar, proc, cur);
	cur = cw_solo_updatepc(cur, cbyte >> 6);
	if (((cbyte >> 4) & 3) == 1)
		index = index & get_reg(cwar, proc, cur);
	else if (((cbyte >> 4) & 3) == 2)
		index = index & get_dir(cwar, cur);
	else if (((cbyte >> 4) & 3) == 3)
		index = index & get_ind(cwar, proc, cur);
	cur = cw_solo_updatepc(cur, cbyte >> 4);
	proc->carry = put_in_reg(proc, index, cwar->arena[circ(cur, 1)]);
	proc->pc = circ(cur, 2);
}

void	cw_xor(t_cwar *cwar, t_proc *proc)
{
	int	cbyte;
	int	index;
	int	cur;

	cur = circ(proc->pc, 1);
	cbyte = cwar->arena[cur];
	index = 0;
	if (((cbyte >> 6) & 3) == 1)
		index = get_reg(cwar, proc, cur);
	else if (((cbyte >> 6) & 3) == 2)
		index = get_dir(cwar, cur);
	else if (((cbyte >> 6) & 3) == 3)
		index = get_ind(cwar, proc, cur);
	cur = cw_solo_updatepc(cur, cbyte >> 6);
	if (((cbyte >> 4) & 3) == 1)
		index = index ^ get_reg(cwar, proc, cur);
	else if (((cbyte >> 4) & 3) == 2)
		index = index ^ get_dir(cwar, cur);
	else if (((cbyte >> 4) & 3) == 3)
		index = index ^ get_ind(cwar, proc, cur);
	cur = cw_solo_updatepc(cur, cbyte >> 4);
	proc->carry = put_in_reg(proc, index, cwar->arena[circ(cur, 1)]);
	proc->pc = circ(cur, 2);
}

void	cw_or(t_cwar *cwar, t_proc *proc)
{
	int	cbyte;
	int	index;
	int	cur;

	cur = circ(proc->pc, 1);
	cbyte = cwar->arena[cur];
	index = 0;
	if (((cbyte >> 6) & 3) == 1)
		index = get_reg(cwar, proc, cur);
	else if (((cbyte >> 6) & 3) == 2)
		index = get_dir(cwar, cur);
	else if (((cbyte >> 6) & 3) == 3)
		index = get_ind(cwar, proc, cur);
	cur = cw_solo_updatepc(cur, cbyte >> 6);
	if (((cbyte >> 4) & 3) == 1)
		index = index | get_reg(cwar, proc, cur);
	else if (((cbyte >> 4) & 3) == 2)
		index = index | get_dir(cwar, cur);
	else if (((cbyte >> 4) & 3) == 3)
		index = index | get_ind(cwar, proc, cur);
	cur = cw_solo_updatepc(cur, cbyte >> 4);
	proc->carry = put_in_reg(proc, index, cwar->arena[circ(cur, 1)]);
	proc->pc = circ(cur, 2);
}

void	cw_add(t_cwar *cwar, t_proc *proc)
{
	int	cbyte;
	int	temp;
	int	cur;

	cur = circ(proc->pc, 1);
	cbyte = cwar->arena[cur];
	temp = 0;
	if (cwar->arena[circ(cur, 1)] && cwar->arena[circ(cur, 1)] <= REG_NUMBER
		&& cwar->arena[circ(cur, 2)] && cwar->arena[circ(cur, 2)] <= REG_NUMBER
		&& cwar->arena[circ(cur, 3)] && cwar->arena[circ(cur, 3)] <= REG_NUMBER)
	{
		temp = get_reg(cwar, proc, cur);
		cur = circ(cur, 1);
		temp = temp + get_reg(cwar, proc, cur);
		cur = circ(cur, 2);
		proc->carry = put_in_reg(proc, temp, cwar->arena[cur]);
		proc->pc = circ(cur, 1);
	}
	else
		proc->pc = circ(cur, 4);
}

void	cw_sub(t_cwar *cwar, t_proc *proc)
{
	int	cbyte;
	int	temp;
	int	cur;

	cur = circ(proc->pc, 1);
	cbyte = cwar->arena[cur];
	temp = 0;
	if (cwar->arena[circ(cur, 1)] && cwar->arena[circ(cur, 1)] <= REG_NUMBER
		&& cwar->arena[circ(cur, 2)] && cwar->arena[circ(cur, 2)] <= REG_NUMBER
		&& cwar->arena[circ(cur, 3)] && cwar->arena[circ(cur, 3)] <= REG_NUMBER)
	{
		temp = get_reg(cwar, proc, cur);
		cur = circ(cur, 1);
		temp = temp - get_reg(cwar, proc, cur);
		cur = circ(cur, 2);
		proc->carry = put_in_reg(proc, temp, cwar->arena[cur]);
		proc->pc = circ(cur, 1);
	}
	else
		proc->pc = circ(cur, 4);
}

void	cw_aff(t_cwar *cwar, t_proc *proc)
{
	int	cur;
	int	temp;
	int	cbyte;

	cur = circ(proc->pc, 1);
	cbyte = cwar->arena[cur];
	if (cwar->arena[circ(cur, 1)] && cwar->arena[circ(cur, 1)] <= REG_NUMBER)
	{
		if (cwar->opt->ncurses == 0)
		{
			temp = get_reg(cwar, proc, cur);
			ft_printf("Aff: %c", temp % 256);
		}
	}
	proc->pc = circ(cur, 1);
}

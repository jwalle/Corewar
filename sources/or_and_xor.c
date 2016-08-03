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

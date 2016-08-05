/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_sub_aff.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/03 19:09:45 by jwalle            #+#    #+#             */
/*   Updated: 2016/08/03 19:10:02 by jwalle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

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

	printf("pc = %d, cycle = %d\n", proc->pc ,cwar->cycle);
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

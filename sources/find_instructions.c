/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_instructions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/03 18:01:06 by jwalle            #+#    #+#             */
/*   Updated: 2016/08/03 18:01:26 by jwalle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int				get_wait_time(unsigned char ins)
{
	if (ins == 0x01 || ins == 0x04 || ins == 0x05)
		return (10);
	if (ins == 0x03 || ins == 0x02)
		return (5);
	if (ins == 0x06 || ins == 0x07 || ins == 0x08)
		return (6);
	if (ins == 0x09)
		return (20);
	if (ins == 0x0a)
		return (25);
	if (ins == 0x0e)
		return (50);
	if (ins == 0x0b)
		return (25);
	if (ins == 0x0d)
		return (10);
	if (ins == 0x10)
		return (2);
	if (ins == 0x0c)
		return (800);
	if (ins == 0x0f)
		return (1000);
	return (0);
}

static void		get_ins_two(unsigned char ins, t_cwar *cwar, t_proc *proc)
{
	if (ins == 0x0a)
		cw_loadindex(cwar, proc);
	else if (ins == 0x0b)
		cw_storeindex(cwar, proc);
	else if (ins == 0x0C)
		cw_fork(cwar, proc);
	else if (ins == 0x0d)
		cw_longload(cwar, proc);
	else if (ins == 0x0e)
		cw_longloadindex(cwar, proc);
	else if (ins == 0x0f)
		cw_lfork(cwar, proc);
	else if (ins == 0x10)
		cw_aff(cwar, proc);
}

void			get_instruction(unsigned char ins, t_cwar *cwar, t_proc *proc)
{
	if (ins == 0x01)
		cw_live(cwar, proc);
	else if (ins == 0x02)
		cw_load(cwar, proc);
	else if (ins == 0x03)
		cw_store(cwar, proc);
	else if (ins == 0x04)
		cw_add(cwar, proc);
	else if (ins == 0x05)
		cw_sub(cwar, proc);
	else if (ins == 0x06)
		cw_and(cwar, proc);
	else if (ins == 0x07)
		cw_or(cwar, proc);
	else if (ins == 0x08)
		cw_xor(cwar, proc);
	else if (ins == 0x09)
		cw_zjmp(cwar, proc);
	else
		get_ins_two(ins, cwar, proc);
}

int				is_ins(unsigned char ins)
{
	if (ins > 0x00 && ins <= 0x10)
		return (1);
	return (0);
}

void			find_instruction(t_cwar *cwar, t_proc *proc)
{
	unsigned char	ins;

	ins = cwar->arena[proc->pc];
	cwar->arena_color[proc->pc][1] = 5;
	if (proc->wait > 1)
		proc->wait--;
	else if (proc->wait >= 0)
	{
		if (proc->wait == 1 && is_ins(ins))
		{
			get_instruction(ins, cwar, proc);
			proc->wait = 0;
		}
		else if (proc->wait == 0 && is_ins(ins))
			proc->wait = get_wait_time(ins);
		else
		{
			proc->pc = circ(proc->pc, 1);
		}
	}
}

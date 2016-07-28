/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/24 17:21:57 by jwalle            #+#    #+#             */
/*   Updated: 2016/07/28 17:02:56 by rmicolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

// TODO : game over


void			game_over(t_cwar *cwar)
{
	(void)cwar;
	ft_printf("La partie est finie !\n");
	exit (1);
	return ;
}

void			sync_cycle(t_cwar *cwar)
{
	time_t current_time;

	current_time = time(NULL);
	while (cwar->time_zero + (cwar->cycle / 50)  > current_time)
		current_time = time(NULL);
}

int				get_wait_time(unsigned char ins)
{
	if (ins == 0x0C)
		return (40);
	if (ins == 0x01)
		return (10);
	if (ins == 0x03)
		return (5);
	if (ins == 0x02)
		return (5);
	if (ins == 0x0b)
		return (25);
	if (ins == 0x0d)
		return (10);
	return (0);
}

void			get_instruction(unsigned char ins, t_cwar *cwar, t_proc *proc)
{
	if (ins == 0x0C)
		cw_fork(cwar, proc);
	else if (ins == 0x01)
		cw_live(cwar, proc);
	else if (ins == 0x02)
		cw_load(cwar, proc);
	else if (ins == 0x03)
		cw_store(cwar, proc);
	else if (ins == 0x0d)
		cw_longload(cwar, proc);
	else if (ins == 0x0b)
		cw_storeindex(cwar, proc);
}

int				is_ins(unsigned char ins)
{
	if (ins == 0x0c)
		return (1);
	if (ins == 0x01)
		return (1);
	if (ins == 0x02)
		return (1);
	if (ins == 0x03)
		return (1);
	// if (ins > 0x00 && ins <= 0x0e)
		// return (1);
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

		if (proc->wait == 1  && is_ins(ins))
		{
			get_instruction(ins, cwar, proc);
			proc->wait = 0;
		}
		else if (proc->wait == 0 && is_ins(ins))
			proc->wait = get_wait_time(ins);
		else
			proc->pc = circ(proc->pc, 1);
	}
	// TODO : stuff
}

void			cycle_procs(t_cwar *cwar)
{
	t_proc		*current;

	current = cwar->last;
	if (!current || !cwar->proc)
		game_over(cwar);
	while (current)
	{
		// printf("ID  : %i\n", current->proc_id);

		printf("pc  : %i\n", current->pc);
		
		printf("cycle  : %i\n", cwar->cycle);
		find_instruction(cwar, current);
		current = current->prev;
	}
}

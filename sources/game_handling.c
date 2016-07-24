/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/24 17:21:57 by jwalle            #+#    #+#             */
/*   Updated: 2016/07/24 17:22:06 by jwalle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

// TODO : game over


void			game_over(t_cwar *cwar)
{
	(void)cwar;
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
	return (0);
}

void			get_instruction(unsigned char ins, t_cwar *cwar, t_proc *proc)
{
	if (ins == 0x0C)
		cw_fork(cwar, proc);
}

int				is_ins(unsigned char ins)
{
	if (ins == 0x0c)
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
			proc->pc++;
	}
	// TODO : stuff
}

void			cycle_procs(t_cwar *cwar)
{
	t_proc		*current;

	current = cwar->proc;
	if (!current)
		game_over(cwar);
	while (current)
	{
		find_instruction(cwar, current);
		current = current->next;
	}
}

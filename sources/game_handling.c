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

void			find_instruction(t_cwar *cwar, t_proc *proc)
{
	unsigned char	ins;

	ins = cwar->arena[proc->pc];

	cwar->arena_color[proc->pc][1] = 5;
	if (proc->wait > 1)
		proc->wait--;
	else if (proc->wait >= 0)
	{
		if (ins == 0x0C && proc->wait == 1)
		{
			cw_fork(cwar, proc);
			proc->wait--;
		}
		else if (ins == 0x0C && proc->wait == 0)
			proc->wait = 40;
		else
			proc->pc++;
			// if (ins > 0x00 && 0x0e)
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

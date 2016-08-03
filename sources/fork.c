/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/23 18:41:59 by jwalle            #+#    #+#             */
/*   Updated: 2016/07/23 18:42:06 by jwalle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		get_new_fork_pc(t_cwar *cwar, t_proc *proc)
{
	int		index;
	int		pc;
	int		i;

	i = 1;
	index = 0;
	while (i <= IND_SIZE)
	{
		index <<= 8;
		index += cwar->arena[circ(proc->pc, i)];
		i++;
	}
	pc = (short)index;
	return (pc);
}

char	cw_zjmp(t_cwar *cwar, t_proc *proc) 
{
	int		new_pc;

	new_pc = get_new_fork_pc(cwar, proc);
	// if (proc->carry) // uncomment when carry set on other ins
		proc->pc = circ(proc->pc, new_pc % IDX_MOD	);
	return (1);
}

char	cw_lfork(t_cwar *cwar, t_proc *proc)
{
	int		new_pc;

	new_pc = get_new_fork_pc(cwar, proc);

	cw_fork_proc(cwar, circ(proc->pc, new_pc), proc, 1);

	proc->pc = circ(proc->pc, 3);
	return (1);
}

char	cw_fork(t_cwar *cwar, t_proc *proc)
{
	int		new_pc;

	new_pc = get_new_fork_pc(cwar, proc);

	cw_fork_proc(cwar, circ(proc->pc, new_pc % IDX_MOD), proc, 1);

	proc->pc = circ(proc->pc, 3);
	return (1);
}
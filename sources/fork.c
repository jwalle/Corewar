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

	index = (cwar->arena[proc->pc + 1] << 8) + cwar->arena[proc->pc + 2];

	if (index > 32767)
		pc = index - 65535;
	else
		pc = index;
	mvprintw(20, 200, "pc : ");
	mvprintw(20, 210, ft_itoa(pc));
	
	return (pc);
}

char	cw_fork(t_cwar *cwar, t_proc *proc)
{
	int		new_pc;

	new_pc = get_new_fork_pc(cwar, proc);
	cw_fork_proc(cwar, proc->pc + new_pc, proc, 1);
	proc->pc += 3;
	return (1);
}
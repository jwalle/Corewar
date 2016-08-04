/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/03 18:23:26 by jwalle            #+#    #+#             */
/*   Updated: 2016/08/03 18:23:39 by jwalle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		find_process(t_cwar *cwar, t_proc *proc, t_proc *prev)
{
	if (prev->next == proc)
	{
		if (cwar->opt->verbose)
			ft_printf("The process ID (%d) as been killed.\n",
				proc->proc_id);
		prev->next = prev->next->next;
		free(proc);
		return (1);
	}
	return (0);
}

t_proc	*destroy_process(t_cwar *cwar, t_proc *proc, t_proc *prev)
{
	int		i;
	int		kill;

	i = 0;
	kill = 0;
	while (i <= REG_NUMBER)
		free(proc->reg[i++]);
	free(proc->reg);
	if (cwar->proc == proc)
	{
		cwar->proc = proc->next;
		free(proc);
		kill++;
	}
	else
		kill = find_process(cwar, proc, prev);
	if (!kill)
		cw_error("The process to kill wasn't found\n", cwar);
	cwar->proc_number--;
	if (!cwar->proc_number)
		game_over(cwar);

	return (cwar->proc);
}

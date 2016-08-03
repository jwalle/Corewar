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

int		find_process(t_proc *proc, t_proc *temp)
{
	while (temp)
	{
		if (temp->next == proc)
		{
			temp->next = temp->next->next;
			free(proc);
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}

void	destroy_process(t_cwar *cwar, t_proc *proc)
{
	int		i;
	t_proc	*temp;
	int		kill;

	i = 0;
	kill = 0;
	while (i <= REG_NUMBER)
		free(proc->reg[i++]);
	free(proc->reg);
	temp = cwar->proc;
	if (temp == proc)
	{
		cwar->proc = proc->next;
		free(proc);
		kill++;
	}
	else
		kill = find_process(proc, temp);
	if (!kill)
		cw_error("The process to kill wasn't found", cwar);
	cwar->proc_number--;
	if (!cwar->proc_number)
		game_over(cwar);
}

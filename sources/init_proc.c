/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_proc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/18 16:30:01 by jwalle            #+#    #+#             */
/*   Updated: 2016/07/25 21:29:54 by rmicolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	destroy_process(t_cwar *cwar, t_proc *proc)
{
	int		i;
	t_proc	*temp;

	// printf("destroy_process : %i\n", proc->proc_id);
	// printf("nb of process : %i\n", cwar->proc_number);

	i = 0;
	// while (i <= REG_NUMBER)
		// free(proc->reg[i++]); \\ TODO : free the registry
	free(proc->reg);
	temp = cwar->proc;
	if (temp == proc)
	{
		cwar->proc = proc->next;
		free(proc);
	}
	else
	{
		while(temp->next)
		{
			if (temp->next == proc)
			{
				temp->next = temp->next->next;
				free(proc);
			}
			temp = temp->next;
		}
	}
	cwar->proc_number--;
	if (!cwar->proc_number)
		game_over(cwar);
	// printf("end of destroy_process\n");
}


void	cw_add_proc(t_proc *new, t_cwar *cwar)
{
	t_proc *tmp;

	if (cwar->proc)
	{
		tmp = cwar->proc;
		new->next = tmp;
		cwar->proc = new;
	}
	else
		cwar->proc = new;
	cwar->proc_number++;	
}

char	cw_first_proc(t_cwar *cwar, int program_counter, int id)
{
	t_proc		*new;
	int			i;
	int			pnum;

	i = 0;
	if (!(new = (t_proc *)malloc(sizeof(t_proc))))
		cw_perror("Malloc failed.", cwar);
	if (!(new->reg = (unsigned char **)malloc(sizeof(unsigned char *) * REG_NUMBER + 1)))
		cw_perror("Malloc failed.", cwar);
	while (i <= REG_NUMBER)
	{
		new->reg[i] = (unsigned char *)malloc(sizeof(unsigned char) * (REG_SIZE + 1));
		ft_bzero(new->reg[i], REG_SIZE + 1);
		i++;
	}
	new->pc = program_counter;
	i = REG_SIZE - 1;
	pnum = 0 - id;
	while (i >= 0)
	{
		new->reg[1][i--] = pnum & 0xff;
		pnum >>= 8;
	}		
	new->carry = 1;
	new->alive = 0;
	new->wait = 0;
	new->next = NULL;
	new->prev = NULL;
	new->player_id = id;
	new->proc_id = cwar->proc_number + 1;
	cw_add_proc(new, cwar);	// MAX PROCESS ?
	return (1);
}

char	cw_fork_proc(t_cwar *cwar, int program_counter, t_proc *old, int id)
{
	t_proc	*new;
	int		i;

	i = 0;
	if (!(new = (t_proc *)malloc(sizeof(t_proc))))
		cw_perror("Malloc failed.", cwar);
	if (!(new->reg = (unsigned char **)malloc(sizeof(unsigned char *) * REG_NUMBER + 1)))
		cw_perror("Malloc failed.", cwar);
	while (i <= REG_NUMBER)
	{
		new->reg[i] = (unsigned char *)malloc(sizeof(unsigned char) * (REG_SIZE + 1));
		ft_memcpy(new->reg[i], old->reg[i], sizeof(old->reg[i]));
		i++;
	}
	new->pc = program_counter;
	new->carry = 1;
	new->wait = 0;
	new->alive = 0;
	new->next = NULL;
	new->prev = NULL;
	new->player_id = id;
	new->proc_id = cwar->proc_number + 1;
	cw_add_proc(new, cwar);	// MAX PROCESS ?
	return (1);
}

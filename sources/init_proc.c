/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_proc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/18 16:30:01 by jwalle            #+#    #+#             */
/*   Updated: 2016/07/18 16:30:04 by jwalle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	*destroy_process(void)
{
	return (NULL);
}

void	cw_add_proc(t_proc *new, t_player *player)
{
	t_proc *tmp;

	if (player->proc)
	{
		if (player->proc->next)
		{
			tmp = player->proc;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new;
		}
		else
			player->proc->next = new;
	}
	else
		player->proc = new;
	player->proc_number++;
}

char	cw_first_proc(t_cwar *cwar, unsigned char *program_counter, t_player *player)
{
	t_proc		*new;
	int			i;

	i = 0;
	if (!(new = (t_proc *)malloc(sizeof(t_proc))))
		cw_perror("Malloc failed.", cwar);
	if (!(new->reg = (void *)malloc(sizeof(void *))))
		cw_perror("Malloc failed.", cwar);\
	while (i < REG_NUMBER)
	{
		new->reg[i] = (int)malloc(REG_SIZE + 1);		//(void* !?? uns_char*)
		//ft_bzero((char *)new->reg[i], REG_SIZE + 1);
		i++;
	}
	new->pc = program_counter;
	new->reg[0] = player->id;
	new->carry = 1;
	new->next = NULL;
	player->proc = new;
	player->proc_number++;
	//cw_add_proc(new, player);	// MAX PROCESS ?
	return (1);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_proc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/18 16:30:01 by jwalle            #+#    #+#             */
/*   Updated: 2016/08/05 00:56:33 by rmicolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

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

void	put_info_proc(t_proc *new, int id)
{
	int	i;
	int	pnum;

	i = REG_SIZE - 1;
	pnum = 0 - id;
	while (i >= 0)
	{
		new->reg[1][i--] = pnum & 0xff;
		pnum >>= 8;
	}
	new->carry = 0;
	new->alive = 0;
	new->wait = 0;
	new->next = NULL;
	new->player_id = id;
}

char	cw_first_proc(t_cwar *cwar, int program_counter, int id)
{
	t_proc		*new;
	int			i;

	i = 0;
	if (!(new = (t_proc *)malloc(sizeof(t_proc))))
		cw_perror("Malloc failed.", cwar);
	if (!(new->reg = (unsigned char **)malloc(sizeof(unsigned char *)
		* REG_NUMBER + 1)))
		cw_perror("Malloc failed.", cwar);
	while (i <= REG_NUMBER)
	{
		new->reg[i] = (unsigned char *)malloc(sizeof(unsigned char)
			* (REG_SIZE + 1));
		ft_bzero(new->reg[i], REG_SIZE + 1);
		i++;
	}
	put_info_proc(new, id);
	new->pc = program_counter;
	new->proc_id = cwar->proc_number + 1;
	cw_add_proc(new, cwar);
	return (1);
}

char	cw_fork_proc(t_cwar *cwar, int pc, t_proc *old)
{
	t_proc	*new;
	int		i;

	i = 0;
	if (!(new = (t_proc *)malloc(sizeof(t_proc))))
		cw_perror("Malloc failed.", cwar);
	if (!(new->reg = (unsigned char **)malloc(sizeof(unsigned char *)
		* REG_NUMBER + 1)))
		cw_perror("Malloc failed.", cwar);
	while (i <= REG_NUMBER)
	{
		new->reg[i] = (unsigned char *)malloc(sizeof(unsigned char)
		* (REG_SIZE + 1));
		ft_memcpy(new->reg[i], old->reg[i], sizeof(old->reg[i]));
		i++;
	}
	new->pc = pc;
	new->carry = 0;
	new->wait = 0;
	new->alive = 0;
	new->next = NULL;
	new->player_id = old->player_id;
	new->proc_id = cwar->proc_number + 1;
	cw_add_proc(new, cwar);
	return (1);
}

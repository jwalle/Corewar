/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmicolon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/24 19:04:54 by rmicolon          #+#    #+#             */
/*   Updated: 2016/08/04 23:36:52 by rmicolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	cw_live(t_cwar *cwar, t_proc *proc)
{
	int			player;
	t_player	*tmp;

	player = -1 * get_dir(cwar, proc->pc);
	tmp = cwar->players;
	if (player > 0)
	{
		while (tmp)
		{
			if (tmp->id == player)
			{
				tmp->last_alive = cwar->cycle;
				tmp->alive++;
				if (cwar->opt->verbose)
					ft_printf("A process said the player %i (%s) is alive !\n",
						player, tmp->header.prog_name);
			}
			tmp = tmp->next;
		}
	}
	proc->alive += 1;
	cwar->lives++;
	proc->pc = circ(proc->pc, 5);
}

int		cw_sti2(t_cwar *cwar, t_proc *proc, int *cur, int cbyte)
{
	int	index;

	index = 0;
	*cur = circ(*cur, 1);
	if (((cbyte >> 4) & 3) == 1)
	{
		index = get_reg(cwar, proc, *cur);
		*cur = circ(*cur, 1);
	}
	else if (((cbyte >> 4) & 3) == 2)
	{
		index = get_sdir(cwar, *cur);
		*cur = circ(*cur, 2);
	}
	else if (((cbyte >> 4) & 3) == 3)
	{
		index = get_ind(cwar, proc, *cur);
		*cur = circ(*cur, 2);
	}
	return (index);
}

void	cw_storeindex(t_cwar *cwar, t_proc *proc)
{
	int				cur;
	unsigned char	cbyte;
	int				adress;

	cur = circ(proc->pc, 1);
	cbyte = cwar->arena[cur];
	adress = 0;
	if (cwar->arena[circ(cur, 1)] && cwar->arena[circ(cur, 1)] <= REG_NUMBER)
	{
		adress = cw_sti2(cwar, proc, &cur, cbyte);
		if (((cbyte >> 2) & 3) == 1)
			adress += get_reg(cwar, proc, cur);
		else if (((cbyte >> 2) & 3) == 2)
			adress += get_sdir(cwar, cur);
		cw_regongrid(cwar, proc->reg[cwar->arena[circ(proc->pc, 2)]],
			circ(proc->pc, (adress % IDX_MOD)), proc);
	}
	proc->pc = cw_updatestipc(proc->pc, cbyte);
}

void	cw_storit(t_cwar *cwar, t_proc *proc, int cur)
{
	int		i;
	int		index;

	i = 1;
	index = 0;
	while (i <= IND_SIZE)
	{
		index <<= 8;
		index += cwar->arena[circ(cur, i++)];
	}
	index = (short)index;
	if (cwar->opt->verbose)
		ft_printf("The process ID (%d) as stored r%d on positon %d.\n",
			proc->proc_id, cwar->arena[cur],
				circ(proc->pc, (index % IDX_MOD)));
	cw_regongrid(cwar, proc->reg[cwar->arena[cur]],
		circ(proc->pc, (index % IDX_MOD)), proc);
}

void	cw_store(t_cwar *cwar, t_proc *proc)
{
	int				cur;
	unsigned char	cbyte;

	cur = circ(proc->pc, 1);
	cbyte = cwar->arena[cur];
	cur = circ(cur, 1);
	if (cwar->arena[cur] && cwar->arena[cur] <= REG_NUMBER)
	{
		if (((cbyte >> 4) & 3) == 1)
			cw_regcpy(proc, cwar->arena[cur], cwar->arena[circ(cur, 1)]);
		if (((cbyte >> 4) & 3) == 3)
			cw_storit(cwar, proc, cur);
	}
	proc->pc = cw_updatepc(proc->pc, cbyte);
}

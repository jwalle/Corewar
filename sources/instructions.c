/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmicolon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/24 19:04:54 by rmicolon          #+#    #+#             */
/*   Updated: 2016/07/25 21:37:38 by rmicolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		cw_updatepc(int pc, int cbyte)
{
	pc = circ(pc, 2);
	while (cbyte)
	{
		if ((cbyte & 3) == 1)
			pc = circ(pc, 1);
		else if ((cbyte & 3) == 2)
			pc = circ(pc, REG_SIZE);
		else if ((cbyte & 3) == 3)
			pc = circ(pc, IND_SIZE);
		cbyte >>= 2;
	}
	return (pc);
}

void	cw_fillreg(t_cwar *cwar, t_proc *proc, unsigned char regnum, int index)
{
	int i;

	if (regnum && regnum <= REG_NUMBER)
	{
		i = 0;
		while (i < REG_SIZE)
		{
			proc->reg[regnum][i++] = cwar->arena[index];
			index = circ(index, 1);
		}
	}
}

void	cw_regcpy(t_proc *proc, unsigned char regn1, unsigned char regn2)
{
	int	i;

	if (regn1 && regn1 <= REG_NUMBER && regn2 && regn2 <= REG_NUMBER)
	{
		i = 0;
		while (i < REG_SIZE)
		{
			proc->reg[regn2][i] = proc->reg[regn2][i];
			++i;
		}
	}
}

void	cw_regongrid(t_cwar *cwar, unsigned char *reg, int index, t_proc *proc)
{
	int	i;

	i = 0;
	while (i < REG_SIZE)
	{
		cwar->arena_color[circ(index, i)][0] = proc->player_id;
		cwar->arena[circ(index, i)] = reg[i];
		++i;
	}
}

void	cw_load(t_cwar *cwar, t_proc *proc)
{
	int				i;
	unsigned char	cbyte;
	int				cur;
	int				index;

	cur = circ(proc->pc, 1);
	cbyte = cwar->arena[cur];
	if (((cbyte >> 6) & 3) == 3)
	{
		i = 1;
		index = 0;
		while (i <= IND_SIZE)
		{
			index <<= 8;
			index += cwar->arena[circ(cur, i)];
			i++; //i = circ(i, 1); ?? IND_SIZE !!
		}
		cw_fillreg(cwar, proc, cwar->arena[circ(cur, IND_SIZE + 1)], circ(proc->pc, (index % IDX_MOD)));
	}
	else if (((cbyte >> 6) & 3) == 2)
		cw_fillreg(cwar, proc, cwar->arena[circ(cur, REG_SIZE + 1)], circ(cur, 1));
	proc->pc = cw_updatepc(proc->pc, cbyte);
}

void	cw_longload(t_cwar *cwar, t_proc *proc)
{
	int				i;
	unsigned char	cbyte;
	int				cur;
	int				index;

	cur = circ(proc->pc, 1);
	cbyte = cwar->arena[cur];
	if (((cbyte >> 6) & 3) == 3)
	{
		i = 1;
		index = 0;
		while (i <= IND_SIZE)
		{
			index <<= 8;
			index += cwar->arena[circ(cur, i)];
			i++; //i = circ(i, 1); ?? IND_SIZE
		}
		cw_fillreg(cwar, proc, cwar->arena[circ(cur, IND_SIZE + 1)], circ(proc->pc, index));
	}
	else if (((cbyte >> 6) & 3) == 2)
		cw_fillreg(cwar, proc, cwar->arena[circ(cur, REG_SIZE + 1)], circ(cur, 1));
	proc->pc = cw_updatepc(proc->pc, cbyte);
}

void	cw_live(t_cwar *cwar, t_proc *proc)
{
	int				player;
	t_player		*tmp;
	int				i;

	i = proc->pc;
	player = (cwar->arena[i = circ(i, 1)] << 24);
	player += (cwar->arena[i = circ(i, 1)] << 16);
	player += (cwar->arena[i = circ(i, 1)] << 8);
	player += (cwar->arena[i = circ(i, 1)]);
	player *= -1;
	tmp = cwar->players;

	//printf("player id = %d\n", player);


	if (player > 0 && player <= cwar->players_nbr)
	{	
		while (tmp)
		{
			//printf("player post if id = %d, tmp id = %d\n", player, tmp->id);
			if (tmp->id == player)
			{
			//	printf("player id = %d, player lives = %d\n", player, tmp->alive);
				tmp->last_alive = cwar->cycle;
				tmp->alive++;
			}
			tmp = tmp->next;
		}
	}
	proc->alive = 1;	
	proc->pc = circ(proc->pc, 5);
}

void	cw_store(t_cwar *cwar, t_proc *proc)
{
	int				cur;
	int				i;
	unsigned char	cbyte;
	int				index;

	cur = circ(proc->pc, 1);
	cbyte = cwar->arena[cur];
	if (cwar->arena[circ(cur, 1)] && cwar->arena[circ(cur, 1)] <= REG_NUMBER)
	{
		if (((cbyte >> 4) & 3) == 1)
			cw_regcpy(proc, cwar->arena[circ(cur, 1)], cwar->arena[circ(cur, 2)]);
		if (((cbyte >> 4) & 3) == 3)
		{
			i = 1;
			index = 0;
			while (i <= IND_SIZE)
			{
				index <<= 8;
				index += cwar->arena[circ(cur, 1 + i)];
				i = circ(i, 1);
			}
			cw_regongrid(cwar, proc->reg[cwar->arena[circ(cur, 1)]], circ(proc->pc, (index % IDX_MOD)), proc);
		}
	}
	proc->pc = cw_updatepc(proc->pc, cbyte);
}

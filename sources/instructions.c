/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmicolon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/24 19:04:54 by rmicolon          #+#    #+#             */
/*   Updated: 2016/07/28 22:06:51 by rmicolon         ###   ########.fr       */
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

int		cw_updatestipc(int pc, int cbyte)
{
	pc = circ(pc, 2);
	while (cbyte)
	{
		if ((cbyte & 3) == 1)
			pc = circ(pc, 1);
		else if ((cbyte & 3) == 2 || (cbyte & 3) == 3)
			pc = circ(pc, 2);
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
			i = circ(i, 1);
		}
		cw_fillreg(cwar, proc, cwar->arena[circ(cur, IND_SIZE + 1)], circ(proc->pc, (index % IDX_MOD)));
	}
	else if (((cbyte >> 6) & 3) == 2)
		cw_fillreg(cwar, proc, cwar->arena[circ(cur, REG_SIZE + 1)], circ(cur, 1));
	proc->pc = cw_updatepc(proc->pc, cbyte);
}

void	cw_loadindex(t_cwar *cwar, t_proc *proc)
{
	int	i;
	unsigned char	cbyte;
	int				cur;
	int				index;
	int				adress;

	cur = circ(proc->pc, 1);
	cbyte = cwar->arena[cur];
	index = 0;
	adress = 0;
	if (((cbyte >> 6) & 3) == 1)
	{
		if (cwar->arena[circ(cur, 2)] && cwar->arena[circ(cur, 2)] <= REG_NUMBER)
		{
			i = 0;
			while (i < REG_SIZE)
			{
				index <<= 8;
				index += proc->reg[cwar->arena[circ(cur, 2)]][i++];
			}
		}
		cur = circ(cur, 3);
	}
	else if (((cbyte >> 6) & 3) == 2)
	{
		i = 1;
		while (i <= 2)
		{
			index <<= 8;
			index += cwar->arena[circ(cur, 1 + i++)];
		}
		index = (short)index;
		cur = circ(cur, 4);
	}
	else if (((cbyte >> 6) & 3) == 3)
	{
		i= 1;
		while (i <= 2)
		{
			adress <<= 8;
			adress += cwar->arena[circ(cur, 1 + i++)];
		}
		adress = (short)adress % IDX_MOD;
		i = 0;
		while (i < REG_SIZE)
		{
			index <<= 8;
			index += cwar->arena[circ(proc->pc, adress + i++)];
		}
		cur = circ(cur, 4);
	}
	adress = index;
	if (((cbyte >> 4) & 3) == 1)
	{
		if (cwar->arena[cur] && cwar->arena[cur] <= REG_NUMBER)
		{
			i = 0;
			while (i < REG_SIZE)
			{
				index <<= 8;
				index += proc->reg[cwar->arena[cur]][i++];
			}
		}
		cur = circ(cur, 1);
	}
	else if (((cbyte >> 4) & 3) == 2)
	{
		i = 0;
		while (i < 2)
		{
			index <<= 8;
			index += cwar->arena[circ(cur, i++)];
		}
		index = (short)index;
		cur = circ(cur, 2);
	}
	adress += index;
	if (cwar->arena[cur] && cwar->arena[cur] <= REG_NUMBER)
		cw_fillreg(cwar, proc, cwar->arena[cur], circ(proc->pc, (adress % IDX_MOD)));
	proc->pc = cw_updatestipc(proc->pc, cbyte);
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
			i = circ(i, 1);
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
	while (tmp)
	{
		if (tmp->id == player)
			tmp->alive++;
		tmp = tmp->next;
	}
	proc->alive = 1;	
	proc->pc = circ(proc->pc, 5);
}

void	cw_storeindex(t_cwar *cwar, t_proc *proc)
{
	int				cur;
	int				i;
	unsigned char	cbyte;
	int				adress;
	int				index;

	cur = circ(proc->pc, 1);
	cbyte = cwar->arena[cur];
	index = 0;
	adress = 0;
	if (cwar->arena[circ(cur, 1)] && cwar->arena[circ(cur, 1)] <= REG_NUMBER)
	{
		if (((cbyte >> 4) & 3) == 1)
		{
			if (cwar->arena[circ(cur, 2)] && cwar->arena[circ(cur, 2)] <= REG_NUMBER)
			{
				i = 0;
				while (i < REG_SIZE)
				{
					index <<= 8;
					index += proc->reg[cwar->arena[circ(cur, 2)]][i++];
				}
			}
			cur = circ(cur, 3);
		}
		else if (((cbyte >> 4) & 3) == 2)
		{
			i = 1;
			while (i <= 2)
			{
				index <<= 8;
				index += cwar->arena[circ(cur, 1 + i++)];
			}
			index = (short)index;
			cur = circ(cur, 4);
		}
		else if (((cbyte >> 4) & 3) == 3)
		{
			i= 1;
			while (i <= 2)
			{
				adress <<= 8;
				adress += cwar->arena[circ(cur, 1 + i++)];
			}
			adress = (short)adress % IDX_MOD;
			i = 0;
			while (i < REG_SIZE)
			{
				index <<= 8;
				index += cwar->arena[circ(proc->pc, adress + i++)];
			}
			cur = circ(cur, 4);
		}
		adress = index;
		if (((cbyte >> 2) & 3) == 1)
		{
			if (cwar->arena[cur] && cwar->arena[cur] <= REG_NUMBER)
			{
				i = 0;
				while (i < REG_SIZE)
				{
					index <<= 8;
					index += proc->reg[cwar->arena[cur]][i++];
				}
			}
		}
		else if (((cbyte >> 2) & 3) == 2)
		{
			i = 0;
			while (i < 2)
			{
				index <<= 8;
				index += cwar->arena[circ(cur, i++)];
			}
			index = (short)index;
		}
		adress += index;
		cw_regongrid(cwar, proc->reg[cwar->arena[circ(proc->pc, 2)]], circ(proc->pc, (adress % IDX_MOD)), proc);
	}
	proc->pc = cw_updatestipc(proc->pc, cbyte);
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
			index = (short)index;
			cw_regongrid(cwar, proc->reg[cwar->arena[circ(cur, 1)]], circ(proc->pc, (index % IDX_MOD)), proc);
		}
	}
	proc->pc = cw_updatepc(proc->pc, cbyte);
}

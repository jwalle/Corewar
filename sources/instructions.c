/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmicolon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/24 19:04:54 by rmicolon          #+#    #+#             */
/*   Updated: 2016/08/03 04:22:12 by rmicolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		get_sdir(t_cwar *cwar, int cur)
{
	int	i;
	int	index;

	i = 1;
	index = 0;
	while (i <= 2)
	{
		index <<= 8;
		index += cwar->arena[circ(cur, i)];
		++i;
	}
	index = (short)index;
	return (index);
}

char	cw_fillreg(t_cwar *cwar, t_proc *proc, unsigned char regnum, int index)
{
	int i;
	int	carry;

	carry = 0;
	if (regnum && regnum <= REG_NUMBER)
	{
		i = 0;
		while (i < REG_SIZE)
		{
			carry <<= 8;
			proc->reg[regnum][i++] = cwar->arena[index];
			carry += cwar->arena[index];
			index = circ(index, 1);
		}
		return (carry == 0) ? 1 : 0;
	}
	return (proc->carry);
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
		cwar->arena_color[circ(index, i)][0] = (proc->player_id % 4) + 1;
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
		proc->carry = cw_fillreg(cwar, proc, cwar->arena[circ(cur,
				IND_SIZE + 1)], circ(proc->pc, (index % IDX_MOD)));
	}
	else if (((cbyte >> 6) & 3) == 2)
		proc->carry = cw_fillreg(cwar, proc,
			cwar->arena[circ(cur, REG_SIZE + 1)], circ(cur, 1));
	proc->pc = cw_updatepc(proc->pc, cbyte);
}

int		cw_ldi2(t_cwar *cwar, t_proc *proc, int *cur, int cbyte)
{
	int	index;

	index = 0;
	if (((cbyte >> 6) & 3) == 1)
		index = get_reg(cwar, proc, *cur);
	else if (((cbyte >> 6) & 3) == 2)
	{
		index = get_sdir(cwar, *cur);
		*cur = circ(*cur, 1);
	}
	else if (((cbyte >> 6) & 3) == 3)
	{
		index = get_ind(cwar, proc, *cur);
		*cur = circ(*cur, 1);
	}
	*cur = circ(*cur, 1);
	return (index);
}

void	cw_loadindex(t_cwar *cwar, t_proc *proc)
{
	unsigned char	cbyte;
	int				cur;
	int				adress;

	cur = circ(proc->pc, 1);
	cbyte = cwar->arena[cur];
	adress = cw_ldi2(cwar, proc, &cur, cbyte);
	if (((cbyte >> 4) & 3) == 1)
		adress += get_reg(cwar, proc, cur);
	else if (((cbyte >> 4) & 3) == 2)
	{
		adress += get_sdir(cwar, cur);
		cur = circ(cur, 1);
	}
	cur = circ(cur, 2);
	if (cwar->arena[cur] && cwar->arena[cur] <= REG_NUMBER)
		cw_fillreg(cwar, proc, cwar->arena[cur],
			circ(proc->pc, (adress % IDX_MOD)));
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
		proc->carry = cw_fillreg(cwar, proc, cwar->arena[
			circ(cur, IND_SIZE + 1)], circ(proc->pc, index));
	}
	else if (((cbyte >> 6) & 3) == 2)
		proc->carry = cw_fillreg(cwar, proc, cwar->arena[
			circ(cur, REG_SIZE + 1)], circ(cur, 1));
	proc->pc = cw_updatepc(proc->pc, cbyte);
}

void	cw_longloadindex(t_cwar *cwar, t_proc *proc)
{
	int				i;
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
		if (cwar->arena[circ(cur, 1)] && cwar->arena[circ(cur, 1)] <= REG_NUMBER)
		{
			i = 0;
			while (i < REG_SIZE)
			{
				index <<= 8;
				index += proc->reg[cwar->arena[circ(cur, 1)]][i++];
			}
		}
		cur = circ(cur, 2);
	}
	else if (((cbyte >> 6) & 3) == 2)
	{
		i = 1;
		while (i <= 2)
		{
			index <<= 8;
			index += cwar->arena[circ(cur, i++)];
		}
		index = (short)index;
		cur = circ(cur, 3);
	}
	else if (((cbyte >> 6) & 3) == 3)
	{
		i = 1;
		while (i <= 2)
		{
			adress <<= 8;
			adress += cwar->arena[circ(cur, i++)];
		}
		adress = (short)adress % IDX_MOD;
		i = 0;
		while (i < REG_SIZE)
		{
			index <<= 8;
			index += cwar->arena[circ(proc->pc, adress + i++)];
		}
		cur = circ(cur, 3);
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
		index = (short)index; // has been uncommented (-> further testing required)
		cur = circ(cur, 2);
	}
	adress += index;
	if (cwar->arena[cur] && cwar->arena[cur] <= REG_NUMBER)
		proc->carry = cw_fillreg(cwar, proc, cwar->arena[cur], circ(proc->pc, adress));
	proc->pc = cw_updatestipc(proc->pc, cbyte);
}

void	cw_live(t_cwar *cwar, t_proc *proc)
{
	int			player;
	t_player	*tmp;

	player = -1 * get_dir(cwar, proc->pc);

	tmp = cwar->players;
	// printf("COUCOU JE suis un proc de %d, ma vie est : %d\n", proc->player_id, player);
	if (player > 0)
	{
		while (tmp)
		{
			if (tmp->id == player)
			{
				tmp->last_alive = cwar->cycle;
				tmp->alive++;
				if (cwar->opt->verbose)
					ft_printf("A process said the player %i (%s) is alive !!!\n",
						player, tmp->header.prog_name);	
			}
			tmp = tmp->next;
		}
	}
	proc->alive += 1;
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
			index = get_reg(cwar, proc, cur);
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
			i = 1;
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
	/*if (verbose)
		ft_printf("The process ID (%d) stored the index from adress  ",);*/
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
			if (cwar->opt->verbose)
				ft_printf("The process ID (%d) as stored r%d on positon %d.\n",
					proc->proc_id, cwar->arena[circ(cur, 1)], circ(proc->pc, (index % IDX_MOD)));
			// printf("index = %i\n", index);
			// printf("index avec IDX_MOD = %i\n", index % IDX_MOD);
			/*printf("proc->pc = %i, index = %i, content registre = %.2x %.2x %.2x %.2x\n", proc->pc, index,
				proc->reg[cwar->arena[circ(cur, 1)]][0],
				proc->reg[cwar->arena[circ(cur, 1)]][1],
				proc->reg[cwar->arena[circ(cur, 1)]][3],
				proc->reg[cwar->arena[circ(cur, 1)]][4]);*/
			
			cw_regongrid(cwar, proc->reg[cwar->arena[circ(cur, 1)]], circ(proc->pc, (index % IDX_MOD)), proc);
		}
	}
	proc->pc = cw_updatepc(proc->pc, cbyte);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/24 17:21:57 by jwalle            #+#    #+#             */
/*   Updated: 2016/07/28 21:39:19 by rmicolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

// TODO : game over


void			cw_ncurses_win(int i, char *player)
{
	mvprintw(30, 200, "And the winner is player");
	mvprintw(30, 225, ft_itoa(i));
	mvprintw(30, 227, ":");
	set_color(i);
	mvprintw(30, 229, player);
	unset_color(i);
	refresh();
	// cwar->pause = 1;
	sleep(3);
	endwin();
	curs_set(1);
	exit(1);
}


void			game_over(t_cwar *cwar)
{
	int			i;
	int			last;
	t_player	*cur;
	char		*player;

	i = 0;
	last = 0;
	cur = cwar->players;
	player = ft_strnew(PROG_NAME_LENGTH + 1);
	while (cur)
	{
		if (cur->last_alive >= last)
		{
			last = cur->last_alive;
			i = cur->id;
			ft_bzero(player, PROG_NAME_LENGTH + 1); // ??
			ft_strcpy(player, cur->header.prog_name);
		}
		cur = cur->next;
	}
	if (!cwar->opt->ncurses)
	{
		ft_printf("And the winner is player %d : %s !!\n",i ,player);
		exit (1);
	}
	cw_ncurses_win(i, cur->header.prog_name);
}

void			sync_cycle(t_cwar *cwar)
{
	time_t current_time;

	current_time = time(NULL);
	while (cwar->time_zero + (cwar->cycle / 50)  > current_time)
		current_time = time(NULL);
}

int				get_wait_time(unsigned char ins)
{
	if (ins == 0x0c)
		return (800); // 800 !
	if (ins == 0x0f)
		return (1000); // 1000 !!
	if (ins == 0x01)
		return (10);
	if (ins == 0x03)
		return (5);
	if (ins == 0x02)
		return (5);
	if (ins == 0x0a)
		return (25);
	if (ins == 0x0b)
		return (25);
	if (ins == 0x0d)
		return (10);
	return (0);
}

void			get_instruction(unsigned char ins, t_cwar *cwar, t_proc *proc)
{
	// printf("ins = %#x\n", ins);
	
	if (ins == 0x0C)
		cw_fork(cwar, proc);
	else if (ins == 0x0f)
		cw_lfork(cwar, proc);
	else if (ins == 0x01)
		cw_live(cwar, proc);
	else if (ins == 0x02)
		cw_load(cwar, proc);
	else if (ins == 0x03)
		cw_store(cwar, proc);
	else if (ins == 0x0a)
		cw_loadindex(cwar, proc);
	else if (ins == 0x0b)
		cw_storeindex(cwar, proc);
	else if (ins == 0x0d)
		cw_longload(cwar, proc);
}

int				is_ins(unsigned char ins)
{
	if (ins == 0x0c)
		return (1);
	if (ins == 0x0f)
		return (1);
	if (ins == 0x01)
		return (1);
	if (ins == 0x02)
		return (1);
	if (ins == 0x03)
		return (1);
	else if (ins == 0x0a)
		return (1);
	else if (ins == 0x0b)
		return (1);
	else if (ins == 0x0d)
		return (1);
	// if (ins > 0x00 && ins <= 0x0e)
		// return (1);
	return (0);
}

void			find_instruction(t_cwar *cwar, t_proc *proc)
{
	unsigned char	ins;

	ins = cwar->arena[proc->pc];
	cwar->arena_color[proc->pc][1] = 5;
	if (proc->wait > 1)
		proc->wait--;
	else if (proc->wait >= 0)
	{

		if (proc->wait == 1  && is_ins(ins))
		{
			get_instruction(ins, cwar, proc);
			proc->wait = 0;
		}
		else if (proc->wait == 0 && is_ins(ins))
			proc->wait = get_wait_time(ins);
		else
			proc->pc = circ(proc->pc, 1);
	}
	// TODO : stuff
}

void			cycle_procs(t_cwar *cwar)
{
	t_proc		*current;

	current = cwar->proc;
	if (!current || !cwar->proc)
		game_over(cwar);
	while (current)
	{
//		 printf("ID  : %i\n", current->proc_id);

//		printf("pc  : %i\n", current->pc);
		
//		printf("cycle  : %i\n", cwar->cycle);
		find_instruction(cwar, current);
		current = current->next;
	}
}

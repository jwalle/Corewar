/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/17 17:01:57 by jwalle            #+#    #+#             */
/*   Updated: 2016/07/28 22:14:00 by rmicolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int		print_programs(t_cwar *cwar)
{
	t_player	*cur;
	int			j;
	int			i;

	j = 0;
	i = 0;
	cur = cwar->players;
	while (cur)
	{
		mvprintw(11 + j, 200, "Player");
		print_number(11 + j, 207, cur->id);
		mvprintw(11 + j, 209, " : ");
		set_color((cur->id % 4) + 1);
		mvprintw(11 + j, 212, cur->header.prog_name);
		unset_color((cur->id % 4) + 1);
		mvprintw(12 + j, 205, "Last lives : ");
		print_number(12 + j, 240, cur->last_alive); // last cycles with live
		mvprintw(13 + j, 205, "Lives in current period : ");
		print_number(13 + j, 240, cur->alive);
		cur = cur->next;
		j += 3;
	}
	return (j + 2);
}

static void		print_right_tab(t_cwar *cwar)
{
	int	j;

	time_t current = time(NULL);
	mvprintw(2, 220, "RUNING");
	mvprintw(3, 200, "Cycles/second limit : 50");
	mvprintw(5, 200, "Cycle : ");
	print_number(5, 210, cwar->cycle);
	mvprintw(7, 200, "Seconds : ");
	print_number(7, 210, current - cwar->time_zero);
	mvprintw(9, 200, "Total process : ");
	print_number(9, 220, cwar->proc_number);
	j = print_programs(cwar);
	mvprintw(14 + j, 200, "CYCLE_TO_DIE : ");
	print_number(14 + j, 215, cwar->to_die);
	mvprintw(15 + j, 200, "CYCLE_DELTA  : ");
	print_number(15 + j, 215, CYCLE_DELTA);
	mvprintw(16 + j, 200, "NBR_LIVE     : ");
	print_number(16 + j, 215, NBR_LIVE);
	mvprintw(17 + j, 200, "MAX_CHECKS   : ");
	print_number(17 + j, 215, MAX_CHECKS);
	mvprintw(17 + j, 220, "( check : ");
	print_number(17 + j, 230, cwar->check);
	mvprintw(17 + j, 233, ")");
 }

void			ft_draw(t_cwar *cwar)
{
	attron(COLOR_PAIR(1024));
	draw_line(254, 0);
	draw_line(254, 67);
	draw_coll(67, 0);
	draw_coll(67, 196);
	draw_coll(67, 254);
	attroff(COLOR_PAIR(1024));
	cw_print_mem(cwar);
	print_right_tab(cwar);
	refresh();
	//doupdate();

}

void			check_live(t_cwar *cwar)
{
	t_proc		*current;
	t_player	*player;
	int			lives;

	lives = 0;
	current = cwar->proc;
	while (current)
	{
		lives += current->alive;
		if (current->alive == 0)
			destroy_process(cwar, current);
		else
			current->alive = 0; // TODO Player->alive = 0 ?
		current = current->next;
	}
	cwar->check++;
	if (lives >= NBR_LIVE || cwar->check >= MAX_CHECKS)	
	{
		cwar->check = 0;
		cwar->to_die -= CYCLE_DELTA;
		if (cwar->to_die <= 0)
			game_over(cwar);
		player = cwar->players;
		while (player)
		{
			player->alive = 0;
			player = player->next;
		}
	}	
}

void			cw_game(t_cwar *cwar)
{
	int c;

	c = 0;
	// cwar->to_die -= 1000; // for testing, delete this
	while (1)
	{
		c = getch();
		if (c == ' ')
			(!cwar->pause) ? cwar->pause++ : cwar->pause--;
		if (!cwar->pause)
		{
			cycle_procs(cwar);
			if (cwar->opt->ncurses)
				ft_draw(cwar);
			cwar->cycle++;
			if ((cwar->cycle % CYCLE_TO_DIE) == 0)
				check_live(cwar);
			if (cwar->opt->dump && cwar->opt->dump == cwar->cycle)
				cw_dump_mem(cwar);
		}
			else if (cwar->opt->ncurses)
		{
			mvprintw(2, 220, " PAUSE");
			refresh();
		}
		if (c == 27)
			return ;
		// if ((cwar->cycle % 50) == 0) // improve this
			// sync_cycle(cwar);
	}
}

void	curse_disp(t_cwar *cwar)
{
	setlocale(LC_ALL, ""); // STUPID BONUS
	initscr();
	start_color();
	COLOR_PAIRS = 16;
	ft_init_color();
	curs_set(0);
	nodelay(stdscr, TRUE);
	ft_draw(cwar);
	refresh();
	cw_game(cwar);
	endwin();
	curs_set(1);
}
		
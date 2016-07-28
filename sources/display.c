/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/17 17:01:57 by jwalle            #+#    #+#             */
/*   Updated: 2016/07/27 18:58:21 by jwalle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	print_hex(char hex[10], int x, int y)
{
	int		i;
	int		j;
	char	prt[2];

	j = 0;
	i = 0;
	while (i < 4)
	{		prt[0] = hex[0 + i];
		prt[1] = hex[1 + i];
		mvprintw(x , y + j, prt);
		mvprintw(x , y + 2 + j, " ");
		i++;
		j += 3;
	}
}

static int		print_programs(t_cwar *cwar)
{
	t_player	*cur;
	int			i;
	int			j;

	j = 0;
	i = 1;
	cur = cwar->players;
	while (cur)
	{
		mvprintw(11 + j, 200, "Player");
		mvprintw(11 + j, 207, ft_itoa(i));
		mvprintw(11 + j, 208, " : ");
		set_color(i);
		mvprintw(11 + j, 211, cur->header.prog_name);
		unset_color(i++);


		mvprintw(12 + j, 205, "Last lives : ");
		mvprintw(12 + j, 240, ft_itoa(cur->last_alive)); // last cycles with live

		mvprintw(13 + j, 205, "Lives in current period : ");
		mvprintw(13 + j, 240, ft_itoa(cur->alive));

		cur = cur->next;
		j += 3;
	}
	return (j + 2);
}

static void		print_right_tab(t_cwar *cwar)
{
	int	j;

	time_t current = time(NULL);

	mvprintw(3, 200, "Cycles/second limit : 50");
	mvprintw(5, 200, "Cycle : ");
	mvprintw(5, 210, ft_itoa(cwar->cycle));
	mvprintw(7, 200, "Seconds : ");
	mvprintw(7, 210, ft_itoa(current - cwar->time_zero));

	mvprintw(9, 200, "Total process : ");
	mvprintw(9, 220, ft_itoa(cwar->proc_number));

	j = print_programs(	cwar);

	mvprintw(14 + j, 200, "CYCLE TO DIE : ");
	mvprintw(14 + j, 215, ft_itoa(cwar->to_die));

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
	if (lives >= NBR_LIVE)
		cwar->to_die -= CYCLE_DELTA;
}

void			cw_game(t_cwar *cwar)
{
	int c;

	c = 0;
	// cwar->to_die -= 1200; // for testing, delete this
	while (1)
	{
		c = getch();
		if (c == ' ')
			(!cwar->pause) ? cwar->pause++ : cwar->pause--; // ugllyyyyy
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
		if (c == 27)
			return ;
		//if ((cwar->cycle % 50) == 0) // improve this
		// 	sync_cycle(cwar);
	}
}

void	curse_disp(t_cwar *cwar)
{
	setlocale(LC_ALL, ""); // STUPID BONUS
	initscr();
	start_color();
	COLOR_PAIRS = 2049;
	ft_init_color();
	curs_set(0);
	nodelay(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	ft_draw(cwar);
	refresh();
	cw_game(cwar);
	endwin();
	curs_set(1);
}

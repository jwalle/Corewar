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

void	ft_draw(t_cwar *cwar)
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
}

int		check_process(t_cwar *cwar)
{
	t_proc		*current;
	int			lives;

	if ((current = cwar->proc) == NULL)
		game_over(cwar);
	while(!current->alive)
		current = destroy_process(cwar, current, NULL);
	lives = current->alive;
	while (current && current->next)
	{
		lives += current->alive;
		if (current->next->alive == 0)
			destroy_process(cwar, current->next, current);
		else
			current->next->alive = 0;
		current = current->next;
	}
	return (lives);
}

void	check_live(t_cwar *cwar)
{
	t_player	*player;
	int			lives;

	lives = check_process(cwar);
	cwar->check++;
//	printf("lives = %d\n", lives);
	if (lives >= NBR_LIVE || cwar->check >= MAX_CHECKS)
	{
		cwar->check = 0;
		cwar->to_die -= CYCLE_DELTA;
		if (cwar->to_die <= 0)
			game_over(cwar);
	}
	player = cwar->players;
	while (player)
	{
		player->alive = 0;
		player = player->next;
	}
}

void	cw_game(t_cwar *cwar)
{
	int c;

	c = 0;
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
			if ((++cwar->cycle % cwar->to_die) == 0)
			{
				 //ft_printf("This is cycle nb %i\n", cwar->cycle);
				 //ft_printf("CYCLE_TO_DIE =  %i\n", cwar->to_die);
				check_live(cwar);
				// ft_printf("CYCLE_TO_DIE =  %i\n", cwar->to_die);
			}
				//if (cwar->opt->verbose)
			// printf("dump = %d\n", cwar->opt->dump);
			if (cwar->opt->dump && cwar->opt->dump == cwar->cycle)
				cw_dump_mem(cwar);
		}
		else if (cwar->opt->ncurses)
			cw_blink_pause();
		if (c == 27)
			return ;
	}
}

void	curse_disp(t_cwar *cwar)
{
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

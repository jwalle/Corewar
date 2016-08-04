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

void			cw_ncurses_win(int i, char *player)
{
	mvprintw(40, 200, "And the winner is player");
	mvprintw(40, 225, ft_itoa(i));
	mvprintw(40, 227, ":");
	set_color((i % 4) + 1);
	mvprintw(40, 229, player);
	unset_color((i % 4) + 1);
	refresh();
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
			ft_bzero(player, PROG_NAME_LENGTH + 1);
			ft_strcpy(player, cur->header.prog_name);
		}	
		cur = cur->next;
	}
	if (cwar->opt->ncurses)
		cw_ncurses_win(i, player);
	ft_printf("And the winner is player %d : %s !!\n", i, player);
	exit(1);
}

void			cycle_procs(t_cwar *cwar)
{
	t_proc		*current;

	current = cwar->proc;
	if (!current || !cwar->proc)
		game_over(cwar);
	while (current)
	{
//		printf("ID  : %i\n", current->proc_id);
//		printf("pc  : %i\n", current->pc);
//		printf("cycle  : %i\n", cwar->cycle);
		find_instruction(cwar, current);
		current = current->next;
	}
}

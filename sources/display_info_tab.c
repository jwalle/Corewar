/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_info_tab.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/03 17:26:48 by jwalle            #+#    #+#             */
/*   Updated: 2016/08/03 17:26:57 by jwalle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		cw_blink_pause(void)
{
	if (time(NULL) % 2 == 0)
		mvprintw(2, 220, "* PAUSE * ");
	else
		mvprintw(2, 220, "          ");
	refresh();
}

static int	print_programs(t_cwar *cwar)
{
	t_player	*cur;
	int			j;
	int			i;

	j = 0;
	i = 0;
	cur = cwar->players;
	while (cur)
	{
		mvprintw(12 + j, 200, "Player");
		print_number(12 + j, 207, cur->id);
		mvprintw(12 + j, 209, " : ");
		set_color((cur->id % 4) + 1);
		mvprintw(12 + j, 212, cur->header.prog_name);
		unset_color((cur->id % 4) + 1);
		mvprintw(13 + j, 205, "Last lives : ");
		print_number(13 + j, 240, cur->last_alive);
		mvprintw(14 + j, 205, "Lives in current period : ");
		mvprintw(14 + j, 240, "      ");
		print_number(14 + j, 240, cur->alive);
		cur = cur->next;
		j += 3;
	}
	return (j + 2);
}

void		print_right_tab(t_cwar *cwar)
{
	int		j;
	time_t	current;

	current = time(NULL);
	mvprintw(2, 220, "RUNNING...");
	mvprintw(6, 200, "Cycle : ");
	print_number(6, 210, cwar->cycle);
	mvprintw(8, 200, "Seconds : ");
	print_number(8, 210, current - cwar->time_zero);
	mvprintw(10, 200, "Total process : ");
	print_number(10, 220, cwar->proc_number);
	j = print_programs(cwar);
	mvprintw(15 + j, 200, "CYCLE_TO_DIE : ");
	mvprintw(15 + j, 215, "     ");
	print_number(15 + j, 215, cwar->to_die);
	mvprintw(16 + j, 200, "CYCLE_DELTA  : ");
	print_number(16 + j, 215, CYCLE_DELTA);
	mvprintw(17 + j, 200, "NBR_LIVE     : ");
	print_number(17 + j, 215, NBR_LIVE);
	mvprintw(18 + j, 200, "MAX_CHECKS   : ");
	print_number(18 + j, 215, MAX_CHECKS);
	mvprintw(18 + j, 220, "( check : ");
	print_number(18 + j, 230, cwar->check);
	mvprintw(18 + j, 233, ")");
}

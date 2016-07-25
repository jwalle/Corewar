/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/17 17:01:57 by jwalle            #+#    #+#             */
/*   Updated: 2016/07/17 17:02:00 by jwalle           ###   ########.fr       */
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

void set_color(int temp)
{
	if (!temp)
		return ;
	else if (temp == 1)
		attron(COLOR_PAIR(PLAYER_ONE));
	else if (temp == 2)
		attron(COLOR_PAIR(PLAYER_TWO));
	else if (temp == 3)
		attron(COLOR_PAIR(PLAYER_THREE));
	else if (temp == 4)
		attron(COLOR_PAIR(PLAYER_FOUR));
	else if (temp == 5)
		attron(COLOR_PAIR(CURRENT_PC));
}

void unset_color(int temp)
{
	if (!temp)
		return ;
	else if (temp == 1)
		attroff(COLOR_PAIR(PLAYER_ONE));
	else if (temp == 2)
		attroff(COLOR_PAIR(PLAYER_TWO));
	else if (temp == 3)
		attroff(COLOR_PAIR(PLAYER_THREE));
	else if (temp == 4)
		attroff(COLOR_PAIR(PLAYER_FOUR));
	else if (temp == 5)
		attroff(COLOR_PAIR(CURRENT_PC));
}

int	ft_int_hex_len(unsigned char n)
{
	int i;

	i = 0;
	while (n)
	{
		n /= 16;
		i++;
	}
	return (i);
}

char	*emo(int temp)
{
	if (!temp)
		return ("💀 ");
	else if (temp < 10)
		return ("😜 ");
	else if (temp < 16)
		return ("💩 ");
	else if (temp < 100)
		return ("👙 ");
	else if (temp < 150)
		return ("🍒 ");
	else if (temp < 200)
		return ("🚘 ");
	return ("00");
}

char *make_hex(int temp)
{
	int		j;
	char	*hex;
	char	*base;

	hex = ft_strnew(3);
	base = "0123456789abcdef";
	j = 1;
	ft_bzero(hex, 3);
	// return (emo(temp));
	if (!temp)
		return ("00");
	hex[1] = '0';
	hex[0] = '0';
	while (temp)
	{
		hex[j] = base[temp % 16];
		temp = temp / 16;
		j--;
	}
	return (hex);
}

void	ft_atoi_hex(t_cwar *cwar)
{
	int 				i;
	int					x;
	int					j;

	i = 0;
	x = 2;
	j = 3;
	while(i < (1024 * 4))
	{
		if (j > 194)
		{
			x++;
			j = 3;
		}
		set_color(cwar->arena_color[i][0]);
		set_color(cwar->arena_color[i][1]);
		mvprintw(x, j, make_hex(cwar->arena[i]));
		unset_color(cwar->arena_color[i][0]);
		unset_color(cwar->arena_color[i][1]);
		cwar->arena_color[i][1] = 0;
		i++;
		j += 3;
	}
}

static void		ft_init_color(void)
{
	init_pair(BLACK_ON_GREEN, COLOR_WHITE, COLOR_GREEN);
	init_pair(PLAYER_ONE, COLOR_GREEN, COLOR_BLACK);
	init_pair(PLAYER_TWO, COLOR_YELLOW, COLOR_BLACK);
	init_pair(PLAYER_THREE, COLOR_RED, COLOR_BLACK);
	init_pair(PLAYER_FOUR, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(CURRENT_PC, 0, COLOR_WHITE);
	init_pair(32, COLOR_BLACK, COLOR_CYAN);
	init_pair(64, COLOR_YELLOW, COLOR_CYAN);
	init_pair(128, COLOR_RED, COLOR_CYAN);
	init_pair(256, COLOR_MAGENTA, COLOR_RED);
	init_pair(512, COLOR_YELLOW, COLOR_BLACK);
	init_pair(1024, COLOR_YELLOW, COLOR_GREEN);
	init_pair(2048, COLOR_YELLOW, COLOR_WHITE);
}

static void		draw_line(int x_max, int ya)
{
	int i;

	i = 0;
	while (i <= x_max)
	{
		mvprintw(ya, i, " ");
		i++;
	}
}

static void		draw_coll(int y_max, int xa)
{
	int i;

	i = 0;
	while (i <= y_max)
	{
		mvprintw(i, xa, " ");
		i++;
	}
}

static void		print_programs(int x, t_cwar *cwar)
{
	t_player	*cur;

	cur = cwar->players;
	if (x >= 1)
	{
		mvprintw(11, 200, "Player 1 : ");
		mvprintw(11, 211, cur->header.prog_name);
		mvprintw(12, 200, "lives : ");
		mvprintw(12, 209, ft_itoa(cur->alive));
	}
	if (x >= 2)
	{
		cur = cur->next;
		mvprintw(14, 200, "Player 2 : ");
		mvprintw(14, 211, cur->header.prog_name);
		mvprintw(15, 200, "lives : ");
		mvprintw(15, 209, ft_itoa(cur->alive));
	}
	if (x >= 3)
	{
		cur = cur->next;
		mvprintw(17, 200, "Player 3 : ");
		mvprintw(17, 211, cur->header.prog_name);
		mvprintw(18, 200, "lives : ");
		mvprintw(18, 209, ft_itoa(cur->alive));
	}
	if (x >= 4)
	{
		cur = cur->next;
		mvprintw(20, 200, "Player 4 : ");
		mvprintw(20, 211, cur->header.prog_name);
		mvprintw(21, 200, "lives : ");
		mvprintw(21, 209, ft_itoa(cur->alive));
	}
}

static void		print_right_tab(t_cwar *cwar)
{
	time_t current = time(NULL);

	mvprintw(3, 200, "Cycles/second limit : 50");
	mvprintw(5, 200, "Cycle : ");
	mvprintw(5, 210, ft_itoa(cwar->cycle));
	mvprintw(7, 200, "Seconds : ");
	mvprintw(7, 210, ft_itoa(current - cwar->time_zero));

	mvprintw(9, 200, "Total process : ");
	mvprintw(9, 220, ft_itoa(cwar->proc_number));

	print_programs(cwar->players_nbr, cwar);
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
	ft_atoi_hex(cwar);
	print_right_tab(cwar);
}

int		check_live(t_cwar *cwar, int to_die)
{
	t_proc		*current;
	int			lives;

	lives = 0;
	current = cwar->proc;
	while (current)
	{
		lives += current->alive;
		if (current->alive == 0)
			destroy_process();
		else
			current->alive = 0; // TODO Player->alive = 0 ?
		current = current->next;
	}
	if (lives >= NBR_LIVE)
		to_die -= CYCLE_DELTA;
	return (to_die);
}

void			ft_game(t_cwar *cwar)
{
	int c;
	int	to_die;

	c = 0;
	to_die = CYCLE_TO_DIE;
	while ((c = getch()) != 27)
	{
	//	if (c == 27)
	//		return ;
		cycle_procs(cwar);
		ft_draw(cwar);
		cwar->cycle++;
		if ((cwar->cycle % CYCLE_TO_DIE) == 0)
			to_die = check_live(cwar, to_die);
		if ((cwar->cycle % 50) == 0)
			sync_cycle(cwar);
		refresh();
		//doupdate();
	}
}

void	curse_disp(t_cwar *cwar)
{
	setlocale(LC_ALL, ""); // STUPID BONUS
		cwar->cycle = 0;
	cwar->time_zero = time(NULL);
	initscr();
	start_color();
	COLOR_PAIRS = 2049;
	ft_init_color();
	curs_set(0);
	ft_draw(cwar);
	ft_game(cwar);
	endwin();
	curs_set(1);
}

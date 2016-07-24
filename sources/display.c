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
		set_color(cwar->arena_color[i]);
		mvprintw(x, j, make_hex(cwar->arena[i]));
		unset_color(cwar->arena_color[i]);
		i++;
		j += 3;
	}
}

static void		ft_init_color(void)
{
	init_pair(RED_ON_GREEN, COLOR_RED, COLOR_GREEN);
	init_pair(BLACK_ON_GREEN, COLOR_WHITE, COLOR_GREEN);
	init_pair(PLAYER_ONE, COLOR_GREEN, COLOR_BLACK);
	init_pair(PLAYER_TWO, COLOR_YELLOW, COLOR_BLACK);
	init_pair(PLAYER_THREE, COLOR_RED, COLOR_BLACK);
	init_pair(PLAYER_FOUR, COLOR_MAGENTA, COLOR_BLACK);
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

static void		print_right_tab(t_cwar *cwar)
{
	time_t current = time(NULL);
	unsigned char		*address;

	mvprintw(3, 200, "Cycles/second limit : 50");
	mvprintw(5, 200, "Cycle : ");
	mvprintw(5, 210, ft_itoa(cwar->cycle));
	mvprintw(7, 200, "Seconds : ");
	mvprintw(7, 210, ft_itoa(current - cwar->time_zero));

	address = cwar->arena;

	mvprintw(10, 200, make_hex(address[cwar->cycle])); // MEM TEST !!

	mvprintw(12, 200, "process : ");
	mvprintw(12, 210, ft_itoa(cwar->proc_number));

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

void			sync_cycle(t_cwar *cwar)
{
	time_t current_time;

	current_time = time(NULL);
	while (cwar->time_zero + (cwar->cycle / 50)  > current_time)
		current_time = time(NULL);
}



void			find_instruction(t_cwar *cwar, t_proc *proc)
{
	unsigned char	ins;

	ins = cwar->arena[proc->pc];
	// TODO : stuff
	if (ins == 0x0C)
		cw_fork(cwar, proc);
	mvprintw(15, 200, make_hex(ins)); // MEM TEST !!
	proc->pc++;
}

void			cycle_procs(t_cwar *cwar)
{
	t_proc		*current;

	current = cwar->proc;
	while (current)
	{
		if (!current->wait)
			find_instruction(cwar, current);
		else
			(current->wait--);
		current = current->next;
	}
}

void			ft_game(t_cwar *cwar)
{
	int c;

	c = 0;
	while ((c = getch()) != 27)
	{
	//	if (c == 27)
	//		return ;
		cycle_procs(cwar);
		ft_draw(cwar);
		cwar->cycle++;
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
	curs_set(1+1);
}

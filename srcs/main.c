/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/07 12:54:50 by jwalle            #+#    #+#             */
/*   Updated: 2016/07/07 12:55:49 by jwalle           ###   ########.fr       */
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
	{
		prt[0] = hex[0 + i];
		prt[1] = hex[1 + i];
		mvprintw(x , y + j, prt);
		mvprintw(x , y + 2 + j, " ");
		i++;
		j += 3;
	}
}

void set_color(int temp)
{
	if (temp == 1)
		attron(COLOR_PAIR(1));
	else if (temp > 1 && temp <= 50)
		attron(COLOR_PAIR(64));
	else if (temp > 50 && temp <= 100)
		attron(COLOR_PAIR(1024));
}

void unset_color(int temp)
{
	if (temp == 1)
		attroff(COLOR_PAIR(1));
	else if (temp > 1 && temp <= 50)
		attroff(COLOR_PAIR(16));
	else if (temp > 50 && temp <= 100)
		attroff(COLOR_PAIR(1024));
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
	if (!temp)
		return ("00");
	while (temp)
	{
		hex[j] = base[temp % 16];
		temp = temp / 16;
		j--;
	}
	set_color(temp);
	return (hex);
}

void	ft_atoi_hex(void *ptr, int x, int y)
{
	unsigned char		*address = (unsigned char *)ptr;
	int 				i;
	int					j;
	int					temp;

	(void)y;
	(void)x;
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
		temp = address[i++];
		set_color(temp);
		mvprintw(x, j, make_hex(temp));
		unset_color(temp);
		j += 3;
	}
}

static void		ft_init_color(void)
{
	init_color(COLOR_RED, 500, 300, 200);
	init_color(COLOR_MAGENTA, 304, 200, 209);
	init_color(COLOR_CYAN, 304, 222, 100);
	init_color(COLOR_WHITE, 155 * 4, 160 * 4, 160 * 4);
	init_pair(1, COLOR_RED, COLOR_GREEN);
	init_pair(2, COLOR_BLACK, COLOR_WHITE);
	init_pair(4, COLOR_BLACK, COLOR_YELLOW);
	init_pair(8, COLOR_BLACK, COLOR_RED);
	init_pair(16, COLOR_BLACK, COLOR_MAGENTA);
	init_pair(32, COLOR_BLACK, COLOR_CYAN);
	init_pair(64, COLOR_YELLOW, COLOR_CYAN);
	init_pair(128, COLOR_RED, COLOR_CYAN);
	init_pair(256, COLOR_MAGENTA, COLOR_RED);
	init_pair(512, COLOR_YELLOW, COLOR_BLACK);
	init_pair(1024, COLOR_YELLOW, COLOR_GREEN);
	init_pair(2048, COLOR_YELLOW, COLOR_WHITE);
}

static void		draw_line(t_env *e, int x_max, int ya)
{
	int i;

	i = 0;
	(void)e;
	while (i <= x_max)
	{
		mvprintw(ya, i, " ");
		i++;
	}
}

static void		draw_coll(t_env *e, int y_max, int xa)
{
	int i;

	i = 0;
	(void)e;
	while (i <= y_max)
	{
		mvprintw(i, xa, " ");
		i++;
	}
}

static void		draw_mem(t_env *e)
{
	int 	i;
	int 	j;
	size_t	n;

	n = 0;
	i = 2;
	j = 2;
	// attron(COLOR_PAIR(8));
	strcpy(e->arene, "a char string greater than 16 chars\0");

	ft_atoi_hex(e->arene, i, j);

	// attroff(COLOR_PAIR(8));
}

void			ft_draw(t_env *e)
{
	int line;
	int rang;
	int xa;
	int	ya;

	clear();
	line = 0;
	xa = e->x * 2;
	ya = 0;
	attron(COLOR_PAIR(1024));
	//while (line < 5)
	//{
	draw_line(e, 254, 0);
	draw_line(e, 254, 67);
	draw_coll(e, 67, 0);
	draw_coll(e, 67, 196);
	draw_coll(e, 67, 254);
	attroff(COLOR_PAIR(1024));

	draw_mem(e);

	//	line++;
//	}
	rang = 0;
	while (rang < 5)
	{
		//draw_cell(e, rang);
		rang++;
	}
}

void			ft_game(t_env *e)
{
	int c;

	while ((c = getch()))
	{
		if (c == 27)
			return ;
		ft_draw(e);
		//getmaxyx(stdscr, e->row, e->col);
		//e->x = ft_cell_size(e->size_board);
		refresh();
	}
}

int main(void)
{
	t_env	e;

	e.arene = malloc(1000);
	// printf("PLOP\n");
	initscr();
	start_color();
	COLOR_PAIRS = 2049;
	ft_init_color();
	curs_set(0);
	e.x = 5;
	ft_draw(&e);

	ft_game(&e);
	
	endwin();
		curs_set(1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/07 12:54:50 by jwalle            #+#    #+#             */
/*   Updated: 2016/07/14 15:46:09 by jwalle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <locale.h> //STUPID BONUS

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
	/*if (!temp)
		return ("💀 ");
	else if (temp < 10)
		return ("😜 ");
	else if (temp < 50)
		return ("💩 ");
	else if (temp < 100)
		return ("👙 ");
	else if (temp < 150)
		return ("🍒 ");
	else if (temp < 200)
		return ("🚘 ");*/
	if (!temp)
		return ("00");
	while (temp)
	{
		hex[j] = base[temp % 16];
		temp = temp / 16;
		j--;
	}
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

void			ft_draw(t_env *e)
{
	clear();
	attron(COLOR_PAIR(1024));
	draw_line(e, 254, 0);
	draw_line(e, 254, 67);
	draw_coll(e, 67, 0);
	draw_coll(e, 67, 196);
	draw_coll(e, 67, 254);
	attroff(COLOR_PAIR(1024));
	ft_atoi_hex(e->arene, 2, 2);
}

void			ft_game(t_env *e)
{
	int c;

	while ((c = getch()))
	{
		if (c == 27)
			return ;
		ft_draw(e);
		refresh();
	}
}

void	curse_disp(t_env *e)
{
	setlocale(LC_ALL, ""); // STUPID BONUS
	initscr();
	start_color();
	COLOR_PAIRS = 2049;
	ft_init_color();
	curs_set(0);
	ft_draw(e);
	ft_game(e);
	endwin();
	curs_set(1);
}

int main(void)
{
	t_env	e;


	e.arene = malloc(1000);
	e.x = 5;
	curse_disp(&e);
	return (0);
}


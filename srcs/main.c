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

void	ft_atoi_hex(void *ptr, int x, int y)
{
	char				*base;
	unsigned char		address;
	char				hex[3];
	int					i;

	base = "0123456789abcdef";
	ft_bzero(hex, 3);
	i = 2;
	x = 2;
//	while(x++ < 100)
	//{
		address = (unsigned char)(ptr);
		while (address)
		{
			hex[i] = base[address % 16];
			address = address / 16;
			i--;
		}
		print_hex(hex, x, y);
	//	x++;
	//}
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
	while (i < x_max)
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
	void	*ptr;

	n = 0;
	i = 2;
	j = 2;
	// attron(COLOR_PAIR(8));
	ptr = e->arene;

	///while (i <= 60)
	//{
	//	j = 2;
	//	while (j <= 190	)
	//	{
			//mvprintw(0,j, ptr);
	ft_atoi_hex(ptr + n, i, j);
		//	n += 8;
			// mvprintw(i, j, "00");
	//		j += 12;
//		}
	//	i += 1;
//	}
	// ft_atoi_hex(e);
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
	draw_line(e, 254, 64);
	draw_coll(e, 64, 0);
	draw_coll(e, 64, 200);
	draw_coll(e, 64, 254);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_misc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/26 18:13:55 by jwalle            #+#    #+#             */
/*   Updated: 2016/07/26 18:14:13 by jwalle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	ft_init_color(void)
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

void	draw_line(int x_max, int ya)
{
	int i;

	i = 0;
	while (i <= x_max)
	{
		mvprintw(ya, i, " ");
		i++;
	}
}

void	draw_coll(int y_max, int xa)
{
	int i;

	i = 0;
	while (i <= y_max)
	{
		mvprintw(i, xa, " ");
		i++;
	}
}

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
		mvprintw(x, y + j, prt);
		mvprintw(x, y + 2 + j, " ");
		i++;
		j += 3;
	}
}

void	print_number(int i, int j, int nb)
{
	char *tmp;

	tmp = ft_itoa(nb);
	mvprintw(i, j, tmp);
	free(tmp);
}

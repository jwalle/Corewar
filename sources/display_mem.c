/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_mem.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/26 18:17:25 by jwalle            #+#    #+#             */
/*   Updated: 2016/07/26 18:17:39 by jwalle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void set_color(int temp)
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

static void unset_color(int temp)
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

char		*make_hex(int temp)
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

void		cw_print_mem(t_cwar *cwar)
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

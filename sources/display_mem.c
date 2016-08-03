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

void	set_color(int temp)
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

void	unset_color(int temp)
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

char	*make_hex(int temp)
{
	int			j;
	char		*hex;
	char		*base;

	if (!temp)
		return (ft_strdup("00"));
	hex = ft_strnew(3);
	base = "0123456789abcdef";
	j = 1;
	ft_bzero(hex, 3);
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

void	cw_print_mem(t_cwar *cwar)
{
	int		i;
	int		x;
	int		j;
	char	*hex;

	i = 0;
	x = 2;
	j = 3;
	while (i < (1024 * 4))
	{
		if (j > 194)
		{
			x++;
			j = 3;
		}
		hex = make_hex(cwar->arena[i]);
		set_color(cwar->arena_color[i][0]);
		set_color(cwar->arena_color[i][1]);
		mvprintw(x, j, hex);
		free(hex);
		unset_color(cwar->arena_color[i][0]);
		unset_color(cwar->arena_color[i][1]);
		cwar->arena_color[i++][1] = 0;
		j += 3;
	}
}

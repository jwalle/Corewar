/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/07 12:56:21 by jwalle            #+#    #+#             */
/*   Updated: 2016/07/07 12:58:12 by jwalle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
#define COREWAR_H

# include <stdio.h> // REMOVE THAT
# include "libft.h"
# include <curses.h>

typedef struct	s_env
{
	int			tab[4][4];
	int			empty;
	int			size_board;
	int			x;
	int			col;
	int			row;
}				t_env;

#endif

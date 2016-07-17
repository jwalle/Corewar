/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmicolon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/06 18:27:20 by rmicolon          #+#    #+#             */
/*   Updated: 2016/07/09 02:55:54 by rmicolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H
# include <errno.h>
# include <stdio.h>
# include <fcntl.h>
# include <curses.h>
# include <locale.h> // STUPID BONUS
# include "libft.h"
# include "op.h"
# include <time.h>

# define ANSI_COLOR_RED     "\x1b[31m"
# define ANSI_COLOR_GREEN   "\x1b[32m"
# define ANSI_COLOR_YELLOW  "\x1b[33m"
# define ANSI_COLOR_BLUE    "\x1b[34m"
# define ANSI_COLOR_MAGENTA "\x1b[35m"
# define ANSI_COLOR_CYAN    "\x1b[36m"
# define ANSI_COLOR_RESET   "\x1b[0m"

#define RED_ON_GREEN 1


typedef struct		s_opt
{
	char			ncurses;
}					t_opt;

typedef struct		s_player
{
	header_t		header;
	unsigned char	*pg;
	struct s_player	*next;
}					t_player;

typedef struct		s_cwar
{
	time_t			time_zero;
	int				players_nbr;
	int				cycle;
	t_opt			*opt;
	t_player		*players;
	unsigned char	*arena;
}					t_cwar;


void	curse_disp(t_cwar *cwar);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmicolon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/06 18:27:20 by rmicolon          #+#    #+#             */
/*   Updated: 2016/08/05 00:58:05 by rmicolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H
# include <errno.h>
# include <fcntl.h>
# include <curses.h>
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

# define PLAYER_ONE 1
# define PLAYER_TWO 2
# define PLAYER_THREE 3
# define PLAYER_FOUR 4
# define CURRENT_PC 5
# define BLACK_ON_GREEN 6

typedef unsigned char	t_u8;

typedef struct		s_proc
{
	unsigned char	**reg;
	int				pc;
	int				carry;
	int				wait;
	int				proc_id;
	int				player_id;
	int				alive;
	struct s_proc	*next;
}					t_proc;

typedef struct		s_opt
{
	char			ncurses;
	int				dump;
	char			verbose;
}					t_opt;

typedef struct		s_player
{
	t_header		header;
	unsigned char	*pg;
	int				alive;
	int				last_alive;
	int				id;
	struct s_player	*next;
}					t_player;

typedef struct		s_cwar
{
	time_t			time_zero;
	int				pause;
	int				players_nbr;
	int				cycle;
	int				proc_number;
	int				to_die;
	int				check;
	int				next_check;
	int				lives;
	t_opt			*opt;
	t_player		*players;
	t_proc			*proc;
	unsigned char	*arena;
	unsigned char	**arena_color;
}					t_cwar;

void				curse_disp(t_cwar *cwar);
void				cw_perror(char *str, t_cwar *cwar);
char				cw_first_proc(t_cwar *cwar, int	program_counter, int id);
void				cw_error(char *str, t_cwar *cwar);
char				cw_fork_proc(t_cwar *cwar, int pc, t_proc *old);
void				sync_cycle(t_cwar *cwar);
void				cycle_procs(t_cwar *cwar);
t_proc				*destroy_process(t_cwar *cwar, t_proc *proc, t_proc *prev);
int					circ(int index, int add);
void				cw_game(t_cwar *cwar);
void				game_over(t_cwar *cwar);
int					get_reg(t_cwar *cwar, t_proc *proc, int cur);
int					cw_updatepc(int pc, int cbyte);
int					cw_updatestipc(int pc, int cbyte);
int					cw_solo_updatepc(int pc, int cbyte);
unsigned int		cw_betole(unsigned int a);
int					is_number(char *str);
int					check_if_id_available(t_cwar *cwar, int n);
t_cwar				*cw_init(void);
void				cw_usage(t_cwar *cwar);
t_opt				*cw_opt_init(t_cwar *cwar);
char				cw_new_player(t_header header, int fd, t_cwar *cwar,
					int numb);
void				cw_add_player(t_player *new, t_cwar *cwar);
void				cw_process_args(int argc, char **argv, t_cwar *cwar);

/*
**		ncurses display :
*/

void				print_hex(char hex[10], int x, int y);
void				print_number(int i, int j, int nb);
void				ft_init_color(void);
void				set_color(int temp);
void				unset_color(int temp);
void				cw_print_mem(t_cwar *cwar);
void				draw_coll(int y_max, int xa);
void				draw_line(int x_max, int ya);
void				cw_blink_pause(void);
void				print_right_tab(t_cwar *cwar);

/*
**		Instructions :
*/

void				cw_dump_mem(t_cwar *cwar);
char				cw_zjmp(t_cwar *cwar, t_proc *proc);
void				cw_live(t_cwar *cwar, t_proc *proc);
char				cw_lfork(t_cwar *cwar, t_proc *proc);
char				cw_fork(t_cwar *cwar, t_proc *proc);
void				cw_load(t_cwar *cwar, t_proc *proc);
void				cw_loadindex(t_cwar *cwar, t_proc *proc);
void				cw_longload(t_cwar *cwar, t_proc *proc);
void				cw_storeindex(t_cwar *cwar, t_proc *proc);
void				cw_store(t_cwar *cwar, t_proc *proc);
void				cw_live(t_cwar *cwar, t_proc *proc);
void				cw_and(t_cwar *cwar, t_proc *proc);
void				cw_xor(t_cwar *cwar, t_proc *proc);
void				cw_or(t_cwar *cwar, t_proc *proc);
void				cw_add(t_cwar *cwar, t_proc *proc);
void				cw_sub(t_cwar *cwar, t_proc *proc);
void				cw_longloadindex(t_cwar *cwar, t_proc *proc);
void				cw_aff(t_cwar *cwar, t_proc *proc);

/*
**		Instruction tools :
*/

int					is_ins(unsigned char ins);
void				get_instruction(t_u8 ins, t_cwar *cwar, t_proc *proc);
int					get_wait_time(unsigned char ins);
void				find_instruction(t_cwar *cwar, t_proc *proc);
char				cw_fillreg(t_cwar *cwar, t_proc *proc, t_u8 regnum, int i);
void				cw_regcpy(t_proc *proc, t_u8 regn1, t_u8 regn2);
void				cw_regongrid(t_cwar *cwar, t_u8 *reg, int i, t_proc *proc);
int					get_dir(t_cwar *cwar, int cur);
int					get_sdir(t_cwar *cwar, int cur);
int					get_ind(t_cwar *cwar, t_proc *proc, int cur);
int					get_reg(t_cwar *cwar, t_proc *proc, int cur);
char				put_in_reg(t_proc *proc, int index, unsigned char regnum);

#endif

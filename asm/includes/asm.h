/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/05 06:50:59 by rhoffsch          #+#    #+#             */
/*   Updated: 2016/08/05 06:51:03 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <libcorewar.h>
# include <op.h>

# define BADARG			10
# define INFOERR		11
# define BAD_INS		12
# define BAD_INS_PARAM	13
# define REG_RANGE		14
# define LABEL_404		15
# define INV_LABEL		16
# define DATA_CORRUPT	17

# define INFO_S			"Error in infos strings"
# define OP_TAB_SIZE	16
# define PARAM_TYPE		g_op_tab[ind].param_type[i - 1]

typedef struct		s_label
{
	char			*name;
	struct s_label	*next;
}					t_label;

typedef struct		s_int
{
	int				octet[1];
	int				valid;
	char			*label;
	int				type;
	struct s_int	*next;
}					t_int;

typedef struct		s_ins
{
	char			*ins;
	char			**instab;
	char			*bytecode;
	int				pos;
	int				len;
	t_label			*labels;
	t_int			*done;

	struct s_ins	*next;
}					t_ins;

typedef	struct		s_op
{
	char			*name;
	int				param_amount;
	int				param_type[3];
	unsigned int	opcode;
	int				cycle_amount;
	char			*comment;
	int				octet_param;
	int				index;
}					t_op;

extern t_op			g_op_tab[];

typedef struct		s_env
{
	char			*info[2];
	t_ins			*ins;
	t_int			*done;
	int				prog_size;
	t_header		head;
}					t_env;

t_ins				*read_champ(t_env *e, char *file, t_ins *ptr, t_ins *ins);
void				delete_separator_char(t_ins *ins);
void				ft_free_maillon(t_ins *ins);
void				*ft_exit(char *error, int errorcode);
void				checks(t_env *e);
char				*correct_param_spacing(char *buf);
void				add_label(t_ins *ptr, char *label);

void				encode(t_env *e);
void				check_label_chars(char *label);
t_int				*is_indirect(char *arg, int ntypes);
t_int				*is_direct(char *arg, int ntypes);
t_int				*is_register(char *arg, int ntypes);
t_int				*new_bytecode(int octet, int valid, char *label, int type);
void				complete_labels(t_env *e);
void				complete_octets_list(t_env *e);

void				write_file(t_env *e, char *filename);

void				ft_putnbrendl(int n);
void				ft_dumptab(char **tab);
void				print_instructions(t_env *e);
void				check_instructions(t_ins *ins);
void				print_octets(t_env *e);

#endif

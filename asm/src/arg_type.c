/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/05 06:49:32 by rhoffsch          #+#    #+#             */
/*   Updated: 2016/08/05 06:49:36 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

void		debug_param(char *arg, int ntypes)
{
	return ;
	ft_putstr("\t(| ");
	ft_putstr(arg);
	ft_putchar(32);
	ft_putchar(arg[0]);
	ft_putchar(32);
	ft_putnbr(ntypes);
	ft_putendl(" |)");
}

t_int		*new_bytecode(int octet, int valid, char *label, int type)
{
	t_int	*bytecode;

	if ((bytecode = (t_int*)malloc(sizeof(t_int))) == NULL)
		ft_exit("Malloc failed.", MALLOCFAIL);
	bytecode->octet[0] = octet;
	bytecode->valid = valid;
	bytecode->label = (label == NULL) ? NULL : ft_strdup(label);
	bytecode->type = type;
	bytecode->next = NULL;
	return (bytecode);
}

t_int		*is_register(char *arg, int ntypes)
{
	int	registre;

	debug_param(arg, ntypes);
	if (arg && ft_strlen(arg) > 1 \
		&& arg[0] == 'r' && ft_isdigit_str(arg + 1) == 1 \
		&& (ntypes == 1 || ntypes == 3 || ntypes == 5 || ntypes == 7))
	{
		registre = ft_atoi(arg + 1);
		if (registre <= REG_NUMBER && registre != 0)
			return (new_bytecode(registre, 1, NULL, REG_CODE));
		ft_exit("Register number out of range.", REG_RANGE);
	}
	return (NULL);
}

t_int		*is_direct(char *arg, int ntypes)
{
	debug_param(arg, ntypes);
	if (arg && ft_strlen(arg) > 1 && arg[0] == DIRECT_CHAR \
		&& (ntypes == 2 || ntypes == 3 || ntypes == 6 || ntypes == 7))
	{
		if (arg[1] == LABEL_CHAR && ft_strlen(arg) > 2)
		{
			check_label_chars(arg + 2);
			return (new_bytecode(0, 0, arg + 2, DIR_CODE));
		}
		else if ((arg[1] == '-' && ft_isdigit_str(arg + 2) == 1) || \
			ft_isdigit_str(arg + 1) == 1)
			return (new_bytecode(ft_atoi(arg + 1), 1, NULL, DIR_CODE));
		else
			ft_exit("Error with parameters.", BAD_INS_PARAM);
	}
	return (NULL);
}

t_int		*is_indirect(char *arg, int ntypes)
{
	debug_param(arg, ntypes);
	if (arg && (ntypes == 4 || ntypes == 5 || ntypes == 6 || ntypes == 7))
	{
		if ((arg[0] == '-' && ft_isdigit_str(arg + 1) == 1) || \
			ft_isdigit_str(arg) == 1)
			return (new_bytecode(ft_atoi(arg), 1, NULL, IND_CODE));
		else if (arg[0] == LABEL_CHAR && ft_strlen(arg) > 1)
		{
			check_label_chars(arg + 2);
			return (new_bytecode(0, 0, arg + 1, IND_CODE));
		}
	}
	return (NULL);
}

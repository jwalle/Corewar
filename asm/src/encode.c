/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encode.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/05 06:49:46 by rhoffsch          #+#    #+#             */
/*   Updated: 2016/08/05 06:49:48 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

static void		encode_param_bytecode(t_ins *ins)
{
	t_int			*ptr;
	unsigned char	a;
	int				i;

	i = 6;
	a = 0b00000000;
	ptr = ins->done->next;
	while (ptr != NULL)
	{
		a = a | (ptr->type << i);
		i -= 2;
		ptr = ptr->next;
	}
	ptr = new_bytecode(a, 1, NULL, 0);
	ptr->next = ins->done->next;
	ins->done->next = ptr;
}

static void		encode_instruction(t_ins *ptr, int ind, int i, int j)
{
	t_int	*last;
	t_int	*tmp;

	ptr->done = new_bytecode(g_op_tab[ind].opcode, 1, NULL, 0);
	last = ptr->done;
	while (ptr->instab[i] != NULL)
	{
		if ((tmp = is_register(ptr->instab[i], PARAM_TYPE)) == NULL)
		{
			j = 2;
			if ((tmp = is_direct(ptr->instab[i], PARAM_TYPE)) != NULL)
				j = (g_op_tab[ind].index == 0) ? 4 : 2;
			else if ((tmp = is_indirect(ptr->instab[i], PARAM_TYPE)) == NULL)
				ft_exit("Error with parameters.", BAD_INS_PARAM);
			tmp->valid = j;
		}
		last->next = tmp;
		last = last->next;
		i++;
	}
}

static int		find_instruction(char *instruction)
{
	int		i;

	i = 0;
	while (i < OP_TAB_SIZE)
	{
		if (ft_strcmp(instruction, g_op_tab[i].name) == 0)
			return (i);
		i++;
	}
	return (-1);
}

void			encode(t_env *e)
{
	t_ins	*ptr;
	int		ind;

	ptr = e->ins;
	while (ptr != NULL)
	{
		if (ptr->instab[0] != NULL)
		{
			if ((ind = find_instruction(ptr->instab[0])) < 0)
				ft_exit("Unknow/unsupported instruction.", BAD_INS);
			if (g_op_tab[ind].param_amount != ft_tablen(ptr->instab + 1))
				ft_exit("Bad arguments.", BAD_INS);
			encode_instruction(ptr, ind, 1, 0);
			if (g_op_tab[ind].octet_param == 1)
				encode_param_bytecode(ptr);
		}
		ptr = ptr->next;
	}
	complete_labels(e);
	complete_octets_list(e);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complete_labels.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/05 06:49:14 by rhoffsch          #+#    #+#             */
/*   Updated: 2016/08/05 06:49:17 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

static int		get_label_pos(t_ins *ins, char *label)
{
	t_ins	*ptr;
	t_label	*ptr2;

	ptr = ins;
	while (ptr != NULL)
	{
		ptr2 = ptr->labels;
		while (ptr2 != NULL)
		{
			if (ptr2 != NULL && ft_strcmp(ptr2->name, label) == 0)
				return (ptr->pos);
			ptr2 = ptr2->next;
		}
		ptr = ptr->next;
	}
	ft_exit("Label in parameter not found.", LABEL_404);
	return (0);
}

static void		complete_labels_param(t_env *e)
{
	t_ins	*ptr;
	t_int	*ptr2;

	ptr = e->ins;
	while (ptr != NULL)
	{
		ptr2 = ptr->done;
		while (ptr2 != NULL)
		{
			if (ptr2->valid != 1 && ptr2->label != NULL)
				ptr2->octet[0] = get_label_pos(e->ins, ptr2->label) - ptr->pos;
			ptr2 = ptr2->next;
		}
		ptr = ptr->next;
	}
}

static void		complete_labels_pos(t_env *e)
{
	t_ins	*ptr;
	t_int	*ptr2;
	int		pos;

	pos = 1;
	ptr = e->ins;
	while (ptr != NULL)
	{
		ptr->pos = pos;
		ptr2 = ptr->done;
		while (ptr2 != NULL)
		{
			pos += ptr2->valid;
			ptr2 = ptr2->next;
		}
		ptr = ptr->next;
	}
	e->prog_size = pos - 1;
}

void			complete_labels(t_env *e)
{
	complete_labels_pos(e);
	complete_labels_param(e);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_champ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/05 06:49:54 by rhoffsch          #+#    #+#             */
/*   Updated: 2016/08/05 06:49:56 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

static t_ins	*clear_labels_from_instructon(t_ins *ins)
{
	t_ins	*ptr;

	ptr = ins;
	while (ptr != NULL)
	{
		if (ptr->instab[0][ft_strlen(ptr->instab[0]) - 1] == LABEL_CHAR)
		{
			add_label(ptr, ptr->instab[0]);
			ptr->instab = ptr->instab + 1;
		}
		ptr = ptr->next;
	}
	return (ins);
}

static t_ins	*labels(t_ins *ins, t_ins *back, t_ins *current, t_ins *next)
{
	back = NULL;
	current = ins;
	next = current->next;
	while (current != NULL)
	{
		if (ft_strchr(current->instab[0], LABEL_CHAR) != NULL \
			&& current->instab[1] == NULL && next != NULL)
		{
			next->labels = current->labels;
			add_label(next, current->instab[0]);
			if (back != NULL)
				back->next = next;
			else
				ins = next;
			ft_free_maillon(current);
		}
		else
			back = current;
		current = next;
		if (current != NULL)
			next = current->next;
	}
	return (clear_labels_from_instructon(ins));
}

static t_ins	*clean_instructions(t_ins *ins)
{
	t_ins	*back;
	t_ins	*current;
	t_ins	*next;

	back = NULL;
	current = ins;
	next = current->next;
	while (current != NULL)
	{
		if (ft_strlen(current->ins) == 0)
		{
			if (back != NULL)
				back->next = next;
			else
				ins = next;
			ft_free_maillon(current);
		}
		else
			back = current;
		current = next;
		if (current != NULL)
			next = current->next;
	}
	return (labels(ins, back, current, next));
}

static t_ins	*new_instruction(char *buf)
{
	t_ins	*ins;
	char	*ptr;
	char	*tmp;

	tmp = correct_param_spacing(buf);
	if ((ptr = ft_strchr(tmp, ';')) != NULL)
		ptr[0] = '\0';
	if ((ptr = ft_strchr(tmp, COMMENT_CHAR)) != NULL)
		ptr[0] = '\0';
	ft_trim(&tmp);
	ins = (t_ins*)ft_malloc(sizeof(t_ins));
	ins->ins = tmp;
	ins->instab = ft_strsplit(tmp, 32);
	ins->bytecode = NULL;
	ins->pos = -1;
	ins->len = -1;
	ins->labels = NULL;
	ins->next = NULL;
	return (ins);
}

t_ins			*read_champ(t_env *e, char *file, t_ins *ptr, t_ins *ins)
{
	int		fd;
	char	*buf;
	int		intro;

	intro = 0;
	if ((fd = open(file, O_RDONLY)) == -1)
		ft_exit("Failed to open file.", OPENFAIL);
	while (intro < 2 && get_next_line(fd, &buf) > 0)
	{
		if (ft_strlen(e->info[intro]) > 0)
			e->info[intro] = ft_strjoin(e->info[intro], "\n");
		e->info[intro] = ft_strjoin(e->info[intro], buf);
		if (ft_strlen(buf) > 0 && buf[ft_strlen(buf) - 1] == '\"')
			intro++;
	}
	while (intro == 2 && get_next_line(fd, &buf) > 0)
	{
		(ptr == NULL) ? ptr = new_instruction(buf) : (void)fd;
		if (ins == NULL)
			ins = ptr;
		else
			ptr->next = new_instruction(buf);
		(ptr->next != NULL) ? ptr = ptr->next : (void)fd;
	}
	return ((intro != 2) ? ft_exit(INFO_S, INFOERR) : clean_instructions(ins));
}

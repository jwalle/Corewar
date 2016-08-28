/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/05 06:50:39 by rhoffsch          #+#    #+#             */
/*   Updated: 2016/08/05 06:50:41 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

void		*ft_exit(char *error, int errorcode)
{
	ft_putendl(error);
	exit(errorcode);
	return (NULL);
}

void		ft_free_maillon(t_ins *ins)
{
	int	i;

	free(ins->ins);
	i = 0;
	while (ins->instab[i] != NULL)
	{
		free(ins->instab[i]);
		i++;
	}
	free(ins->instab);
	free(ins);
}

void		delete_separator_char(t_ins *ins)
{
	t_ins	*ptr;
	int		i;

	ptr = ins;
	while (ptr != NULL)
	{
		i = 0;
		while (ptr->instab[i] != NULL)
		{
			if (ptr->instab[i][ft_strlen(ptr->instab[i]) - 1] == SEPARATOR_CHAR)
				ptr->instab[i][ft_strlen(ptr->instab[i]) - 1] = '\0';
			i++;
		}
		ptr = ptr->next;
	}
}

char		*correct_param_spacing(char *buf)
{
	int		i;
	int		j;
	int		v;
	char	*correct;

	v = 0;
	i = 0;
	while (buf[i] != '\0')
		v = (buf[i++] == ',') ? v + 1 : v;
	v += ft_strlen(buf) + 1;
	if ((correct = (char*)malloc(sizeof(char) * v)) == NULL)
		ft_exit("Malloc failed.", MALLOCFAIL);
	i = 0;
	j = 0;
	while (i < v)
	{
		correct[i] = buf[j];
		if (buf[j] == ',' && buf[j + 1] != 32)
			correct[++i] = 32;
		i++;
		j++;
	}
	correct[i] = '\0';
	return (correct);
}

void		add_label(t_ins *ptr, char *label)
{
	t_label		*ptr2;

	ptr2 = ptr->labels;
	if (ptr2 == NULL)
	{
		if ((ptr->labels = (t_label*)malloc(sizeof(t_label))) == NULL)
			ft_exit("Malloc failed.", MALLOCFAIL);
		ptr->labels->name = ft_strdup(label);
		ptr->labels->name[ft_strlen(ptr->labels->name) - 1] = '\0';
		ptr->labels->next = NULL;
	}
	else
	{
		while (ptr2->next != NULL)
			ptr2 = ptr2->next;
		if ((ptr2->next = (t_label*)malloc(sizeof(t_label))) == NULL)
			ft_exit("Malloc failed.", MALLOCFAIL);
		ptr2->next->name = ft_strdup(label);
		ptr2->next->name[ft_strlen(ptr2->next->name) - 1] = '\0';
		ptr2->next->next = NULL;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/05 06:50:15 by rhoffsch          #+#    #+#             */
/*   Updated: 2016/08/05 06:50:17 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

static char		*ft_grep(char *str, int len)
{
	char	*dst;
	int		i;
	int		q;

	i = len;
	q = 0;
	while (str[i] == 32 || str[i] == '\t')
		i++;
	if (str[i] != '\"')
		ft_exit("Error in infos strings", INFOERR);
	dst = ft_strdup(str + i + 1);
	dst[ft_strlen(dst) - 1] = '\0';
	while (str[i] != '\0')
	{
		if (str[i] == '\"')
			q++;
		if (q == 2 && str[i + 1] != '\0')
			ft_exit("Error in infos strings", INFOERR);
		i++;
	}
	if (q != 2 || str[i - 1] != '\"')
		ft_exit("Error in infos strings", INFOERR);
	free(str);
	return (dst);
}

static void		clean_infos(t_env *e)
{
	char	*ptr;

	while (e->info[0][0] == COMMENT_CHAR || e->info[0][0] == ';' \
		|| ft_linelen(e->info[0]) == 0)
	{
		ptr = e->info[0];
		e->info[0] = ft_strdup(e->info[0] + ft_linelen(e->info[0]) + 1);
		free(ptr);
	}
	while (e->info[1][0] == COMMENT_CHAR || e->info[1][0] == ';' \
		|| ft_linelen(e->info[1]) == 0)
	{
		ptr = e->info[1];
		e->info[1] = ft_strdup(e->info[1] + ft_linelen(e->info[1]) + 1);
		free(ptr);
	}
}

void			check_label_chars(char *label)
{
	int		i;

	i = 0;
	while (label[i] != '\0')
	{
		if (ft_strchr(LABEL_CHARS, label[i]) == NULL)
			ft_exit("Error: invalid character(s) in label.", INV_LABEL);
		i++;
	}
}

void			check_all_label_chars(t_ins *ins)
{
	t_ins	*ptr;
	t_label	*ptr2;

	ptr = ins;
	while (ptr != NULL)
	{
		ptr2 = ptr->labels;
		while (ptr2 != NULL)
		{
			check_label_chars(ptr2->name);
			ptr2 = ptr2->next;
		}
		ptr = ptr->next;
	}
}

void			checks(t_env *e)
{
	char	*ptr;
	int		name;
	int		com;

	clean_infos(e);
	name = ft_strlen(NAME_CMD_STRING);
	com = ft_strlen(COMMENT_CMD_STRING);
	if (ft_strncmp(e->info[0], NAME_CMD_STRING, name) == 0 \
		&& ft_strncmp(e->info[1], COMMENT_CMD_STRING, com) == 0)
		;
	else if (ft_strncmp(e->info[1], NAME_CMD_STRING, name) == 0 \
		&& ft_strncmp(e->info[0], COMMENT_CMD_STRING, com) == 0)
	{
		ptr = e->info[0];
		e->info[0] = e->info[1];
		e->info[1] = ptr;
	}
	else
		ft_exit("Error in infos", INFOERR);
	if (ft_strlen(e->info[0] = ft_grep(e->info[0], name)) > PROG_NAME_LENGTH \
		|| ft_strlen(e->info[1] = ft_grep(e->info[1], com)) > COMMENT_LENGTH)
		ft_exit("Error in infos string: too long", INFOERR);
	check_all_label_chars(e->ins);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/05 06:50:08 by rhoffsch          #+#    #+#             */
/*   Updated: 2016/08/05 06:50:09 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

static void		make_header(t_env *e)
{
	int			i;

	e->head.magic = COREWAR_EXEC_MAGIC;
	e->head.prog_size = e->prog_size;
	i = 0;
	while (i <= PROG_NAME_LENGTH)
	{
		e->head.prog_name[i] = 0;
		i++;
	}
	ft_strcpy(e->head.prog_name, e->info[0]);
	i = 0;
	while (i <= COMMENT_LENGTH)
	{
		e->head.comment[i] = 0;
		i++;
	}
	ft_strcpy(e->head.comment, e->info[1]);
}

int				main(int ac, char **av)
{
	t_env		*e;

	if (ac != 2)
	{
		ft_putendl("Bad number of arguments, must be 1.");
		return (BADARG);
	}
	e = (t_env*)ft_malloc(sizeof(t_env));
	e->info[0] = "";
	e->info[1] = "";
	e->ins = read_champ(e, av[1], NULL, NULL);
	delete_separator_char(e->ins);
	checks(e);
	encode(e);
	make_header(e);
	write_file(e, av[1]);
	return (0);
}

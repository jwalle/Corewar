/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmicolon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/06 18:18:39 by rmicolon          #+#    #+#             */
/*   Updated: 2016/08/05 01:21:15 by rmicolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	cw_set_player_in_arena(t_cwar *cwar, int begin, int i, unsigned int j)
{
	t_player	*tmp;
	int			n;

	n = 0;
	if (cwar->players)
	{
		tmp = cwar->players;
		while (tmp)
		{
			begin = (MEM_SIZE * i) / cwar->players_nbr;
			if (!tmp->id)
				tmp->id = check_if_id_available(cwar, ++n);
			cw_first_proc(cwar, begin, tmp->id);
			j = 0;
			while (j < tmp->header.prog_size)
			{
				cwar->arena_color[begin + j][0] = (tmp->id % 4) + 1;
				cwar->arena[begin + j] = tmp->pg[j];
				j++;
			}
			++i;
			tmp = tmp->next;
		}
	}
}

void	cw_setup_arena(t_cwar *cwar)
{
	int				i;
	unsigned int	j;
	int				begin;

	if (!(cwar->arena = (unsigned char *)malloc(MEM_SIZE + 1)))
		cw_perror("Malloc failed.", cwar);
	ft_bzero(cwar->arena, MEM_SIZE + 1);
	if (!(cwar->arena_color = (unsigned char **)malloc(sizeof(unsigned char *)
		* MEM_SIZE)))
		cw_perror("Malloc failed.", cwar);
	i = 0;
	while (i < MEM_SIZE + 1)
	{
		cwar->arena_color[i] = (unsigned char *)malloc(sizeof(unsigned char)
			* 3);
		ft_bzero(cwar->arena_color[i], sizeof(unsigned char) * 3);
		i++;
	}
	j = 0;
	i = 0;
	begin = 0;
	cw_set_player_in_arena(cwar, begin, i, j);
}

void	cw_introduce(t_cwar *cwar)
{
	t_player	*tmp;
	int			i;

	i = 1;
	ft_printf("Introducing contestants...\n");
	if (cwar->players)
	{
		tmp = cwar->players;
		while (tmp)
		{
			ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
				tmp->id, tmp->header.prog_size, tmp->header.prog_name,
				tmp->header.comment);
			++i;
			tmp = tmp->next;
		}
	}
}

int		main(int argc, char **argv)
{
	t_cwar	*cwar;

	cwar = cw_init();
	if (argc == 1)
		cw_usage(cwar);
	cw_process_args(argc, argv, cwar);
	cw_setup_arena(cwar);
	if (!cwar->opt->ncurses)
	{
		cw_introduce(cwar);
		cw_game(cwar);
	}
	else
		curse_disp(cwar);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/05 05:05:59 by jwalle            #+#    #+#             */
/*   Updated: 2016/08/05 05:06:22 by jwalle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_cwar			*cw_init(void)
{
	t_cwar	*cwar;

	if (!(cwar = (t_cwar *)malloc(sizeof(t_cwar))))
		cw_perror("Malloc failed.", cwar);
	cwar->players_nbr = 0;
	cwar->opt = NULL;
	cwar->players = NULL;
	cwar->arena = NULL;
	cwar->proc = NULL;
	cwar->cycle = 0;
	cwar->to_die = CYCLE_TO_DIE;
	cwar->proc_number = 0;
	cwar->time_zero = time(NULL);
	cwar->pause = 0;
	cwar->check = 0;
	cwar->lives = 0;
	cwar->next_check = CYCLE_TO_DIE;
	return (cwar);
}

t_opt			*cw_opt_init(t_cwar *cwar)
{
	t_opt	*opt;

	if (!(opt = (t_opt *)malloc(sizeof(t_opt))))
		cw_perror("Malloc failed.", cwar);
	opt->ncurses = 0;
	opt->dump = 0;
	opt->verbose = 0;
	return (opt);
}

void			cw_print_usage(void)
{
	ft_printf("Usage: ./corewar [-v -n -dump N] ");
	ft_printf("[-number N] <champion1.cor> <...>\n");
	ft_printf("\t-v\t\t: verbose (prints various ");
	ft_printf("informations about then game walkthrough.)\n");
	ft_printf("\t-n\t\t: provide Ncurses visualisation of the game.\n");
	ft_printf("\t-dump N\t\t: Dumps the memory after N cycles, ");
	ft_printf("then exit the game.\n");
	ft_printf("\t-number N\t: give the next specified player the number N.\n");
}

void			cw_usage(t_cwar *cwar)
{
	t_player *tmp;

	if (cwar)
	{
		if (cwar->opt)
			free(cwar->opt);
		if (cwar->players)
		{
			while (cwar->players && cwar->players->next)
			{
				tmp = cwar->players;
				while (tmp->next->next)
					tmp = tmp->next;
				if (tmp->next->pg)
					free(tmp->next->pg);
				free(tmp->next);
				tmp->next = NULL;
			}
			free(cwar->players);
		}
		free(cwar);
	}
	cw_print_usage();
	exit(1);
}

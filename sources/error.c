/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/18 16:30:11 by jwalle            #+#    #+#             */
/*   Updated: 2016/07/18 16:30:25 by jwalle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	cw_perror(char *str, t_cwar *cwar)
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
	perror(str);
	exit (1);
}

void	cw_error(char *str, t_cwar *cwar)
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
	ft_printf("%s", str);
	exit (1);
}

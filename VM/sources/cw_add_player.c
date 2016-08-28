/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_add_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/05 05:27:14 by jwalle            #+#    #+#             */
/*   Updated: 2016/08/06 17:11:46 by jwalle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		cw_check_arg(char *arg, t_cwar *cwar, int numb)
{
	int				fd;
	int				ret;
	t_header		header;

	if ((fd = open(arg, O_RDONLY)) < 0)
		cw_perror(arg, cwar);
	if ((ret = read(fd, &header, sizeof(t_header))) < 0)
		cw_perror(arg, cwar);
	if (ret != sizeof(t_header))
		cw_error(ft_strjoin(arg, " is too small to be a champion\n"), cwar);
	header.magic = cw_betole(header.magic);
	header.prog_size = cw_betole(header.prog_size);
	if (header.prog_size > CHAMP_MAX_SIZE)
		cw_error(ft_strjoin(arg, " is too big\n"), cwar);
	if (header.magic != COREWAR_EXEC_MAGIC)
		cw_error(ft_strjoin(arg, " has wrong header\n"), cwar);
	if (!cw_new_player(header, fd, cwar, numb))
		cw_error(ft_strjoin(arg, " is too small\n"), cwar);
	close(fd);
}

int			cw_case_args(char **argv, t_cwar *cwar, int i)
{
	if (!ft_strcmp(argv[i], "-n"))
		cwar->opt->ncurses = 1;
	else if (!ft_strcmp(argv[i], "-v"))
		cwar->opt->verbose = 1;
	else if (!ft_strcmp(argv[i], "-dump"))
	{
		if (is_number(argv[i + 1]))
			cwar->opt->dump = ft_atoi(argv[i + 1]);
		else
			cw_usage(cwar);
		i++;
	}
	else if (!ft_strcmp(argv[i], "-number"))
	{
		if (is_number(argv[i + 1]))
			cw_check_arg(argv[i + 2], cwar, ft_atoi(argv[i + 1]));
		else
			cw_usage(cwar);
		i += 2;
	}
	else
		cw_check_arg(argv[i], cwar, 0);
	return (i);
}

void		cw_process_args(int argc, char **argv, t_cwar *cwar)
{
	int i;

	i = 1;
	cwar->opt = cw_opt_init(cwar);
	while (i < argc)
	{
		i = cw_case_args(argv, cwar, i);
		i++;
	}
}

void		cw_add_player(t_player *new, t_cwar *cwar)
{
	t_player *tmp;

	if (cwar->players)
	{
		if (cwar->players->next)
		{
			tmp = cwar->players;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new;
		}
		else
			cwar->players->next = new;
	}
	else
		cwar->players = new;
	cwar->players_nbr++;
}

char		cw_new_player(t_header header, int fd, t_cwar *cwar, int numb)
{
	int			ret;
	t_player	*new;

	if (!(new = (t_player *)malloc(sizeof(t_player))))
		cw_perror("Malloc failed.", cwar);
	new->header = header;
	if (!(new->pg = (unsigned char *)malloc(header.prog_size + 1)))
		cw_perror("Malloc failed.", cwar);
	if ((ret = read(fd, new->pg, header.prog_size)) < 0)
		cw_perror(header.prog_name, cwar);
	if (ret != (int)header.prog_size)
		return (0);
	new->id = numb;
	new->next = NULL;
	new->alive = 0;
	new->last_alive = 0;
	if (cwar->players_nbr < MAX_PLAYERS)
		cw_add_player(new, cwar);
	else
	{
		ft_printf("Too much players, %d is the max allowed\n", MAX_PLAYERS);
		cw_error(NULL, cwar);
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmicolon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/06 18:18:39 by rmicolon          #+#    #+#             */
/*   Updated: 2016/07/28 20:09:24 by rmicolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_cwar	*cw_init(void)
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
	return (cwar);
}

t_opt	*cw_opt_init(t_cwar *cwar)
{
	t_opt	*opt;

	if (!(opt = (t_opt *)malloc(sizeof(t_opt))))
		cw_perror("Malloc failed.", cwar);
	opt->ncurses = 0;
	opt->dump = 0;
	opt->verbose = 0;
	return (opt);
}

void	cw_usage(t_cwar *cwar)
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
	ft_printf("Corewar usage\n");
	exit (1);
}

unsigned int	cw_betole(unsigned int a)
{
	unsigned int	b;
	unsigned char	*src;
	unsigned char	*dst; 

	src = (unsigned char *)&a;
	dst = (unsigned char *)&b;
	dst[0] = src[3];
	dst[1] = src[2];
	dst[2] = src[1];
	dst[3] = src[0];
	return (b);
}

void	cw_add_player(t_player *new, t_cwar *cwar)
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

int	check_if_id_available(t_cwar *cwar, int n)
{
	t_player	*cur;

	cur = cwar->players;
	while (cur)
	{
		if (cur->id == n)
			return(check_if_id_available(cwar, ++n));
		cur = cur->next;
	}
	return (n);
}

char	cw_new_player(header_t header, int fd, t_cwar *cwar, int numb)
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
		cw_error("Too much players (This error should be checked)", cwar);
	return (1);
}

void	cw_check_arg(char *arg, t_cwar *cwar, int numb)
{
	int				fd;
	int				ret;
	header_t		header;

	if ((fd = open(arg, O_RDONLY)) < 0)
		cw_perror(arg, cwar);
	if ((ret = read(fd, &header, sizeof(header_t))) < 0)
		cw_perror(arg, cwar);
	if (ret != sizeof(header_t))
		cw_error("File (insert filename) is too small to be a champion", cwar);	
	header.magic = cw_betole(header.magic);
	header.prog_size = cw_betole(header.prog_size);
	if (header.prog_size > CHAMP_MAX_SIZE)
		cw_error("(insert filename) is too big (this error msg has to be checked !!)", cwar);
	if (header.magic != COREWAR_EXEC_MAGIC)
		cw_error("(insert filename) has wrong header (this error msg has to be checked !!)", cwar);
	if (!cw_new_player(header, fd, cwar, numb))
		cw_error("(insert filename) is too small", cwar);
	close(fd);
}

int		is_number(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while(str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	cw_process_args(int argc, char **argv, t_cwar *cwar)
{
	int i;

	i = 1;
	cwar->opt = cw_opt_init(cwar);
	while (i < argc)
	{
		if (!ft_strcmp(argv[i], "-n"))
			cwar->opt->ncurses = 1;
			else if (!ft_strcmp(argv[i], "-v"))
			cwar->opt->verbose = 1;
		else if (!ft_strcmp(argv[i], "-dump"))
		{
			if (is_number(argv[i + 1])) // IMPORTANT
				cwar->opt->dump = atoi(argv[i + 1]);
			else
				cw_usage(cwar);
			i++;
		}
		else if (!ft_strcmp(argv[i], "-number"))
		{
			if (is_number(argv[i + 1]))
				cw_check_arg(argv[i + 2], cwar, ft_atoi(argv[i + 1])); // doesnt go there if last arg is an option, segfault on ncurses
			else
				cw_usage(cwar);
			i += 2;
		}
		else
			cw_check_arg(argv[i], cwar, 0); // doesnt go there if last arg is an option, segfault on ncurses
		++i;
	}
}

int		circ( int index, int add)
{
	int		i;

	i = (index + add) % MEM_SIZE;
	return (i >= 0 ? i : i + MEM_SIZE);
}

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
			cw_first_proc(cwar, begin , tmp->id);
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
	if (!(cwar->arena_color = (unsigned char **)malloc(sizeof(unsigned char *) * MEM_SIZE)))
		cw_perror("Malloc failed.", cwar);
	i = 0;
	while (i < MEM_SIZE + 1)
	{
		cwar->arena_color[i] = (unsigned char *)malloc(sizeof(unsigned char) * 3); // ... !!
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
			ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n", tmp->id, tmp->header.prog_size, tmp->header.prog_name, tmp->header.comment);
			++i;
			tmp = tmp->next;
		}
	}
}

void	cw_dump_mem(t_cwar *cwar)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (cwar->arena)
	{
		while (i < MEM_SIZE)
		{
			if (!j)
			{
				ft_printf("0x0000 : ");
				j++;
			}
			if (i && ((i) % 64) == 0)
				ft_printf("%#.4x : ", j++ * 64);
			ft_printf("%.2x ", cwar->arena[i]);
			if (((i + 1) % 64) == 0) 
			// if (!i)
			//else
				ft_putchar('\n');
			++i;
		}
	}
	exit (1);
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

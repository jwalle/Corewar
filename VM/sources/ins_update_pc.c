/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ins_update_pc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/03 19:04:49 by jwalle            #+#    #+#             */
/*   Updated: 2016/08/03 19:05:01 by jwalle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		cw_updatepc(int pc, int cbyte)
{
	pc = circ(pc, 2);
	while (cbyte)
	{
		if ((cbyte & 3) == 1)
			pc = circ(pc, 1);
		else if ((cbyte & 3) == 2)
			pc = circ(pc, REG_SIZE);
		else if ((cbyte & 3) == 3)
			pc = circ(pc, IND_SIZE);
		cbyte >>= 2;
	}
	return (pc);
}

int		cw_updatestipc(int pc, int cbyte)
{
	pc = circ(pc, 2);
	while (cbyte)
	{
		if ((cbyte & 3) == 1)
			pc = circ(pc, 1);
		else if ((cbyte & 3) == 2 || (cbyte & 3) == 3)
			pc = circ(pc, 2);
		cbyte >>= 2;
	}
	return (pc);
}

int		cw_solo_updatepc(int pc, int cbyte)
{
	if ((cbyte & 3) == 1)
		pc = circ(pc, 1);
	else if ((cbyte & 3) == 2)
		pc = circ(pc, DIR_SIZE);
	else if ((cbyte & 3) == 3)
		pc = circ(pc, IND_SIZE);
	return (pc);
}

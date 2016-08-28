/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_nbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmicolon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/06 20:51:58 by rmicolon          #+#    #+#             */
/*   Updated: 2016/01/12 15:39:18 by rmicolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		get_next_nbr(char *str, int *nb)
{
	static int	i;

	if (str[i])
	{
		while (str[i] && !ft_isdigit(str[i]) && str[i] != '-')
			i++;
		*nb = ft_atoi(&str[i]);
		while (str[i] && (ft_isdigit(str[i]) || str[i] == '-'))
			i++;
	}
	else
	{
		i = 0;
		return (0);
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmicolon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 16:01:23 by rmicolon          #+#    #+#             */
/*   Updated: 2015/12/03 21:38:44 by rmicolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const char	*sc1;
	const char	*sc2;
	size_t		i;

	sc1 = s1;
	sc2 = s2;
	i = 0;
	while (i < n)
	{
		if (sc1[i] != sc2[i])
			return ((unsigned char)sc1[i] - (unsigned char)sc2[i]);
		i++;
	}
	return (0);
}

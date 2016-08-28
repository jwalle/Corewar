/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmicolon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 15:52:56 by rmicolon          #+#    #+#             */
/*   Updated: 2015/12/13 20:05:23 by rmicolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char const		*s2;
	unsigned char	c2;
	size_t			i;

	s2 = s;
	c2 = c;
	i = 0;
	while (i < n)
	{
		if ((unsigned char)s2[i] == c2)
			return ((void*)&s[i]);
		i++;
	}
	return (NULL);
}

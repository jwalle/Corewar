/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmicolon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 21:27:19 by rmicolon          #+#    #+#             */
/*   Updated: 2015/11/27 18:13:25 by rmicolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*s2;
	char	c2;
	int		slen;

	s2 = (char *)s;
	c2 = c;
	slen = ft_strlen(s2);
	while (slen >= 0)
	{
		if (s2[slen] == c2)
			return (&s2[slen]);
		slen--;
	}
	return (NULL);
}

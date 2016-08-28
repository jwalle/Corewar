/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmicolon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 18:16:06 by rmicolon          #+#    #+#             */
/*   Updated: 2015/12/03 23:27:14 by rmicolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t		i;
	size_t		j;
	size_t		k;

	i = 0;
	j = 0;
	if (s2[j] == '\0')
		return ((char *)s1);
	while (s1[i] != '\0' && i < n)
	{
		k = i;
		while (s2[j] == s1[i] && i < n)
		{
			i++;
			j++;
			if (s2[j] == '\0')
				return ((char *)&s1[k]);
		}
		i = k + 1;
		j = 0;
	}
	return (NULL);
}

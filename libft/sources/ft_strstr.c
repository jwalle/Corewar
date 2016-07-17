/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmicolon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 21:40:20 by rmicolon          #+#    #+#             */
/*   Updated: 2015/11/27 18:12:26 by rmicolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *s1, const char *s2)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	if (s2[j] == '\0')
		return ((char *)s1);
	while (s1[i] != '\0')
	{
		k = i;
		while (s2[j] == s1[i])
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmicolon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/09 17:53:08 by rmicolon          #+#    #+#             */
/*   Updated: 2015/12/13 20:49:16 by rmicolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	size_t	len;
	char	*cpy;
	size_t	i;

	len = ft_strlen(s1);
	if (n < len)
		len = n;
	if (!(cpy = (char*)malloc(sizeof(*cpy) * len + 1)))
		return (NULL);
	i = 0;
	while (s1[i] != '\0' && i < len)
	{
		cpy[i] = s1[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

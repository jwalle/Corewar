/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmicolon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 14:29:48 by rmicolon          #+#    #+#             */
/*   Updated: 2016/06/25 19:54:33 by rmicolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		len;
	char	*cpy;
	int		i;

	len = ft_strlen(s1);
	if (!(cpy = (char*)malloc(sizeof(*cpy) * len + 1)))
		return (NULL);
	i = 0;
	cpy = ft_strcpy(cpy, s1);
	return (cpy);
}

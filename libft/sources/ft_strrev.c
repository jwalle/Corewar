/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmicolon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/13 20:52:11 by rmicolon          #+#    #+#             */
/*   Updated: 2015/12/13 21:26:45 by rmicolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *str)
{
	char	buff;
	size_t	len;
	size_t	i;

	len = ft_strlen(str) - 1;
	i = 0;
	while (i <= len / 2)
	{
		buff = str[i];
		str[i] = str[len];
		str[len] = buff;
		i++;
		len--;
	}
	return (str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmicolon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 15:36:58 by rmicolon          #+#    #+#             */
/*   Updated: 2015/11/27 18:21:11 by rmicolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*buffer;
	char		*dst2;
	const char	*src2;
	size_t		i;

	dst2 = dst;
	src2 = src;
	i = 0;
	if (!(buffer = (char *)malloc(sizeof(*buffer) * len + 1)))
		return (NULL);
	while (i < len)
	{
		buffer[i] = src2[i];
		i++;
	}
	i = 0;
	while (i < len)
	{
		dst2[i] = buffer[i];
		i++;
	}
	free(buffer);
	return (dst);
}

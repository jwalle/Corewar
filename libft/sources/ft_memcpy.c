/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmicolon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 12:51:33 by rmicolon          #+#    #+#             */
/*   Updated: 2015/11/26 14:46:51 by rmicolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*bdst;
	const char	*bsrc;
	size_t		i;

	bdst = dst;
	bsrc = src;
	i = 0;
	while (i < n)
	{
		bdst[i] = bsrc[i];
		i++;
	}
	return (dst);
}

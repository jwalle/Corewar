/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmicolon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 14:52:20 by rmicolon          #+#    #+#             */
/*   Updated: 2015/12/03 21:43:34 by rmicolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char			*bdst;
	const unsigned char		*bsrc;
	unsigned char			d;
	size_t					i;

	bdst = dst;
	bsrc = src;
	d = c;
	i = 0;
	while (i < n)
	{
		bdst[i] = bsrc[i];
		if (bsrc[i] == d)
		{
			return (&dst[i + 1]);
		}
		i++;
	}
	return (NULL);
}

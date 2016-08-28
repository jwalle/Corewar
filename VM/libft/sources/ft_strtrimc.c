/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrimc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmicolon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/11 23:18:37 by rmicolon          #+#    #+#             */
/*   Updated: 2015/12/13 20:49:33 by rmicolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrimc(char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*new;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	if (s[i])
		len = ft_strlen(s) - 1;
	else
		len = 0;
	while (s[i] == c && s[i])
		i++;
	while (s[len] == c && len >= i)
		len--;
	if (!(new = (char *)malloc(sizeof(*new) * ((len - i) + 2))))
		return (NULL);
	while (i <= len)
		new[j++] = s[i++];
	new[j] = '\0';
	return (new);
}

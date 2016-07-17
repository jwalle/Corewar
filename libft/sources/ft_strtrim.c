/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmicolon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 19:51:34 by rmicolon          #+#    #+#             */
/*   Updated: 2015/12/09 17:51:29 by rmicolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
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
	while ((s[i] == ' ' || s[i] == ',' || s[i] == '\n' || s[i] == '\t') && s[i])
		i++;
	while ((s[len] == ' ' || s[len] == ',' || s[len] == '\n' || s[len] == '\t')
			&& len >= i)
		len--;
	if (!(new = (char *)malloc(sizeof(*new) * ((len - i) + 2))))
		return (NULL);
	while (i <= len)
		new[j++] = s[i++];
	new[j] = '\0';
	return (new);
}

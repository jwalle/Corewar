/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmicolon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 20:11:45 by rmicolon          #+#    #+#             */
/*   Updated: 2016/07/04 23:24:57 by rmicolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	ft_count_occurence(char const *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		if (*s != c && *s)
		{
			count++;
			while (*s != c && *s)
				s++;
		}
		else
			s++;
	}
	return (count);
}

static int	ft_start(char const *s, int start, char c)
{
	while (s[start] == c && s[start] != '\0')
		start++;
	return (start);
}

static int	ft_len(char const *s, int start, char c)
{
	int	i;

	i = 0;
	while (s[start] != c && s[start] != '\0')
	{
		start++;
		i++;
	}
	return (i);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**tab;
	int		oc;
	int		i;
	int		start;
	int		len;

	if (!s || !c)
		return (NULL);
	tab = NULL;
	i = 0;
	start = 0;
	len = 0;
	oc = ft_count_occurence(s, c);
	if (!(tab = (char**)malloc(sizeof(*tab) * oc + 1)))
		return (NULL);
	while (i < oc + 1)
		tab[i++] = NULL;
	i = 0;
	while (i < oc)
	{
		start = ft_start(s, start + len, c);
		len = ft_len(s, start, c);
		tab[i++] = ft_strsub(s, start, len);
	}
	return (tab);
}

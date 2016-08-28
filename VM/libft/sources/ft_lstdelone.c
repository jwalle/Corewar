/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmicolon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/04 18:30:32 by rmicolon          #+#    #+#             */
/*   Updated: 2015/12/04 19:36:40 by rmicolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list **alst, void (*del)(void*, size_t))
{
	t_list	*temp;

	temp = *alst;
	if (*alst)
	{
		(*del)(temp->content, temp->content_size);
		free(*alst);
		*alst = NULL;
	}
}

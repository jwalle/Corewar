/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmicolon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/04 20:23:34 by rmicolon          #+#    #+#             */
/*   Updated: 2015/12/05 15:44:35 by rmicolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*begin_new;
	t_list	*tmpnew;
	t_list	*tmplst;

	if (!lst || !f)
		return (NULL);
	tmplst = f(lst);
	if (!(begin_new = ft_lstnew(tmplst->content, tmplst->content_size)))
		return (NULL);
	tmpnew = begin_new;
	lst = lst->next;
	while (lst)
	{
		tmplst = f(lst);
		if (!(tmpnew->next = ft_lstnew(tmplst->content, tmplst->content_size)))
			return (NULL);
		tmpnew = tmpnew->next;
		lst = lst->next;
	}
	return (begin_new);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkheiri <hkheiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 10:07:18 by hkheiri           #+#    #+#             */
/*   Updated: 2021/11/13 20:01:12 by hkheiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*t;
	t_list	*rtn;

	if (!lst)
		return (NULL);
	rtn = ft_lstnew(f(lst->content));
	if (!rtn)
		return (NULL);
	t = rtn;
	lst = lst->next;
	while (lst)
	{
		t->next = ft_lstnew(f(lst->content));
		if (!t->next)
		{
			ft_lstclear(&rtn, del);
			return (NULL);
		}
		t = t->next;
		lst = lst->next;
	}
	return (rtn);
}

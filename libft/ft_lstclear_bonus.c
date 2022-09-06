/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkheiri <hkheiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 10:06:13 by hkheiri           #+#    #+#             */
/*   Updated: 2021/11/11 18:39:05 by hkheiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*t;
	t_list	*tm;

	if (!lst || !del)
		return ;
	t = *lst;
	while (t)
	{
		tm = t->next;
		del(t->content);
		t->next = NULL;
		free(t);
		t = tm;
	}
	*lst = NULL;
}

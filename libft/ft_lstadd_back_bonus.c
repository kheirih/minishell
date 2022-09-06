/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkheiri <hkheiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 10:05:31 by hkheiri           #+#    #+#             */
/*   Updated: 2021/11/17 18:57:21 by hkheiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*t;

	if (lst)
	{
		t = *lst;
		if (t)
		{
			while ((t)->next)
			{
				(t) = (t)->next;
			}
			(t)->next = new;
		}
		else
			*lst = new;
	}
}

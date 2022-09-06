/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkheiri <hkheiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 14:58:37 by hkheiri           #+#    #+#             */
/*   Updated: 2021/11/10 11:53:41 by hkheiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	size_t	i;
	size_t	s_len;

	if (!s || !f)
		return ;
	s_len = ft_strlen(s);
	i = 0;
	while (i < s_len)
	{
		(*f)((unsigned int)i, (s + i));
		i++;
	}
}

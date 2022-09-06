/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkheiri <hkheiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 10:35:52 by hkheiri           #+#    #+#             */
/*   Updated: 2021/11/13 18:08:59 by hkheiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*ptr;
	size_t	s_len;
	size_t	i;

	s_len = ft_strlen(s);
	i = 0;
	ptr = (char *)s;
	while (i <= s_len)
	{
		if (ptr[i] == c)
			return ((char *)(ptr + i));
		i++;
	}
	return (0);
}

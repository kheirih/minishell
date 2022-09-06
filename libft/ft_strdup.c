/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkheiri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 13:05:50 by hkheiri           #+#    #+#             */
/*   Updated: 2021/11/10 11:52:23 by hkheiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	s_len;
	char	*str;

	s_len = ft_strlen(s1);
	str = malloc(sizeof(char) * (s_len + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, s_len + 1);
	return (str);
}

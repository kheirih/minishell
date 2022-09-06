/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkheiri <hkheiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 14:48:51 by hkheiri           #+#    #+#             */
/*   Updated: 2021/11/10 11:54:57 by hkheiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	str_len;
	char	*str;
	size_t	i;

	if (!s1 && !s2)
		return (ft_strdup(""));
	if (!s1 && s2)
		return ((char *)s2);
	if (s1 && !s2)
		return ((char *)s1);
	i = 0;
	str_len = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = (char *)malloc(sizeof(char) * str_len);
	if (!str)
		return (NULL);
	str[0] = '\0';
	ft_strlcat(str, s1, str_len);
	ft_strlcat(str, s2, str_len);
	return (str);
}

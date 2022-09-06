/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkheiri <hkheiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 12:52:04 by hkheiri           #+#    #+#             */
/*   Updated: 2021/11/13 18:09:27 by hkheiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	size_t	str_len;
	size_t	i;

	if (!s)
		return (ft_strdup(""));
	if (!f)
		return (ft_strdup(s));
	str_len = ft_strlen(s);
	str = (char *)malloc(sizeof(char ) * (str_len + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < str_len)
	{
		str[i] = (*f)(i, (char )s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}

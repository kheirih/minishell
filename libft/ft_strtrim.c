/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkheiri <hkheiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 10:13:35 by hkheiri           #+#    #+#             */
/*   Updated: 2021/11/10 12:13:12 by hkheiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	isset(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		front;
	int		back;
	char	*str;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	front = -1;
	while (isset(s1[++front], set))
		;
	if (s1[front] == s1[ft_strlen(s1)])
	{
		str = ft_strdup("");
		if (!str)
			return (NULL);
		return (str);
	}
	back = ft_strlen(s1);
	while (isset(s1[--back], set))
		;
	str = ft_substr(s1, front, back - front + 1);
	if (!str)
		return (NULL);
	return (str);
}

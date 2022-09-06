/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkheiri <hkheiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 10:47:38 by hkheiri           #+#    #+#             */
/*   Updated: 2021/11/11 18:55:04 by hkheiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned int	len_s;
	char			*us;

	len_s = ft_strlen(s);
	us = (char *)s;
	while (len_s > 0)
	{
		if (us[len_s] == c)
			return (us + len_s);
		len_s--;
	}
	if (us[0] == c)
		return (us);
	return (0);
}

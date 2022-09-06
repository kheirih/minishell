/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkheiri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 09:04:06 by hkheiri           #+#    #+#             */
/*   Updated: 2021/11/10 11:58:18 by hkheiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;
	size_t	i;
	size_t	max;

	src_len = ft_strlen(src);
	i = 0;
	max = 0;
	if (dstsize == 0)
		return (src_len);
	if (src_len < dstsize)
		max = src_len;
	else
		max = dstsize - 1;
	while (i < max)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_len);
}

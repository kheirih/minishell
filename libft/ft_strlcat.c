/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkheiri <hkheiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 18:37:04 by hkheiri           #+#    #+#             */
/*   Updated: 2021/11/10 12:54:08 by hkheiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;	
	size_t	max;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	i = 0;
	if (dst_len >= dstsize)
		return (dstsize + src_len);
	if (dstsize <= dst_len + src_len)
		max = dstsize;
	else
		max = dst_len + src_len;
	while (i + dst_len < max)
	{
		dst[i + dst_len] = src[i];
		i++;
	}
	if (max == dstsize)
		dst[dst_len + i - 1] = '\0';
	else
		dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}

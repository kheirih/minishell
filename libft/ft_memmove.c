/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkheiri <hkheiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 18:02:44 by hkheiri           #+#    #+#             */
/*   Updated: 2021/11/13 18:06:35 by hkheiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char		*dest;
	const unsigned char	*source;

	if (!dst && !src)
		return (NULL);
	if (dst < src)
		dst = ft_memcpy(dst, src, n);
	else if (dst == src || n == 0)
		return (dst);
	else
	{
		dest = dst;
		source = src;
		while (--n > 0)
		{
			dest[n] = source[n];
		}
			dest[0] = source[0];
	}
	return (dst);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkheiri <hkheiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 15:17:47 by hkheiri           #+#    #+#             */
/*   Updated: 2021/11/10 11:27:10 by hkheiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nbr_len(int n)
{
	int	i;
	int	sign;

	i = 0;
	sign = 0;
	if (n <= 0)
		sign = 1;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i + sign);
}

static void	chrinstr(char *str, char c)
{
	size_t	s_len;

	s_len = ft_strlen(str);
	str[s_len] = c;
	str[s_len + 1] = '\0';
}

static void	intinchr(char *str, int nbr)
{
	if (nbr == -2147483648)
	{
		ft_strlcat(str, "-2147483648", 12);
		return ;
	}
	else if (nbr < 0)
	{
		chrinstr(str, '-');
		intinchr(str, -nbr);
	}
	else if (nbr > 9)
	{
		intinchr(str, nbr / 10);
		intinchr(str, nbr % 10);
	}
	else
		chrinstr(str, (char )(nbr + '0'));
}

char	*ft_itoa(int n)
{
	char	*str;
	size_t	str_len;

	str_len = nbr_len(n);
	str = (char *)malloc(sizeof(unsigned char ) * (str_len + 1));
	if (!str)
		return (NULL);
	str[0] = '\0';
	intinchr(str, n);
	return (str);
}

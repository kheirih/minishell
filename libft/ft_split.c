/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkheiri <hkheiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 15:26:47 by hkheiri           #+#    #+#             */
/*   Updated: 2021/11/17 18:45:10 by hkheiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nbr_slic(const char *s, char c)
{
	int	i;
	int	nbr_slics;

	nbr_slics = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != 0)
			nbr_slics++;
		i++;
	}
	return (nbr_slics + 1);
}

static void	modified(char *s_d, char c)
{
	int	i;

	i = 0;
	while (s_d[i])
	{
		if (s_d[i] == c)
			s_d[i] = 0;
		i++;
	}
}

static void	freestrs(char **strs, int nbr)
{
	int	i;

	i = 0;
	while (i < nbr)
	{
		free(strs[i]);
		i++;
	}
}

static char	**createstrs(char **strs, char *s, int nbr_parts)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < nbr_parts)
	{
		while (s[j] == 0)
			j++;
		strs[i] = ft_strdup((const char *)(s + j));
		if (!strs[i])
		{
			freestrs(strs, i);
			return (NULL);
		}
		j += ft_strlen(strs[i]);
		i++;
	}
	strs[i] = 0;
	return (strs);
}

char	**ft_split(const char *s, char c)
{
	char	*s_d;
	char	**strs;

	if (!s)
		return (NULL);
	while (*s == c && s)
		s++;
	if (!(*s) || !c)
	{
		strs = malloc(sizeof(char *));
		if (!strs)
			return (NULL);
		strs[0] = NULL;
		return (strs);
	}
	strs = malloc(sizeof(char *) * (nbr_slic(s, c) + 1));
	if (!strs)
		return (NULL);
	s_d = ft_strdup(s);
	modified(s_d, c);
	strs = createstrs(strs, s_d, nbr_slic(s, c));
	free(s_d);
	if (!strs)
		return (NULL);
	return (strs);
}

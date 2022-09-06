/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkheiri <hkheiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 00:03:56 by hkheiri           #+#    #+#             */
/*   Updated: 2022/05/26 00:12:57 by hkheiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob_head.h"

int	iswhite(char c)
{
	if (c == 32 || c == 9 || c == 10)
		return (1);
	return (0);
}

int	ispre(char c)
{
	if (c == '\'')
		return ('\'');
	if (c == '\"')
		return ('\"');
	return (0);
}

int	isspec(char c)
{
	if (ispre(c) || c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}

int	strlen_w(char *str)
{
	int	i;

	i = 0;
	while (str[i] && !iswhite(str[i]) && !isspec(str[i]))
		i++;
	return (i);
}

int	strlen_p(char *str)
{
	int		i;
	char	c;

	i = 0;
	c = *str;
	while (str[i + 1] && str[i + 1] != c)
		i++;
	return (i);
}

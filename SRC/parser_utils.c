/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkheiri <hkheiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 00:42:08 by hkheiri           #+#    #+#             */
/*   Updated: 2022/05/26 00:08:29 by hkheiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob_head.h"

int	isspectok(t_tokl *t)
{
	if (!t)
		return (0);
	if (t->type == PIPET || t->type == RIN || t->type == ROUT
		|| t->type == RAP || t->type == HD)
		return (1);
	return (0);
}

int	cmd_len(t_tokl **tokl)
{
	int		i;
	t_tokl	*p;

	i = 0;
	p = *tokl;
	while (*tokl && !isspectok(*tokl))
	{
		i++;
		(*tokl) = (*tokl)->next;
	}
	(*tokl) = p;
	return (i);
}

t_filel	*get_word(t_tokl **tokl)
{
	t_filel	*file;

	if (isspectok(*tokl))
		(*tokl) = (*tokl)->next;
	file = filel_init((*tokl)->con);
	(*tokl) = (*tokl)->next;
	return (file);
}

void	free_strs(char **str, int in)
{
	int	i;

	i = -1;
	if (in)
	{
		while (++i < in)
			free(str[i]);
		free(str);
		str = NULL;
		return ;
	}
	while (str && str[++i])
		free(str[i]);
	if (str)
		free(str);
	str = NULL;
	return ;
}

int	get_cmd_filel(t_filel **cmdf, t_tokl **tokl)
{
	while ((*tokl) && !isspectok(*tokl))
	{
		if (!filel_add(cmdf, get_word(tokl)))
			return (0);
	}
	return (1);
}

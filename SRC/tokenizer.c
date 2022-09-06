/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkheiri <hkheiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 00:03:49 by hkheiri           #+#    #+#             */
/*   Updated: 2022/05/26 00:15:56 by hkheiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob_head.h"

t_tokl	*get_pre(char **str)
{
	char	*r_token;
	int		tlen;
	int		i;
	char	c;

	tlen = strlen_p(*str);
	r_token = malloc(sizeof(char) * (tlen + 1));
	if (!r_token)
		return (NULL);
	i = -1;
	c = **str;
	(*str)++;
	while (++i < tlen)
	{
		r_token[i] = (**str);
		(*str)++;
	}
	r_token[i] = 0;
	if (c == '\'')
		return (tok_init(r_token, UQ));
	else
		return (tok_init(r_token, DQ));
}

t_tokl	*get_del(char **str)
{
	char	*r_token;
	int		tlen;
	int		i;

	tlen = strlen_w(*str);
	r_token = malloc(sizeof(char) * (tlen + 1));
	if (!r_token)
		return (NULL);
	i = -1;
	while (++i < tlen)
	{
		r_token[i] = (**str);
		(*str)++;
	}
	r_token[i] = 0;
	return (tok_init(r_token, WORD));
}

t_tokl	*tok_init(char *con, int type)
{
	t_tokl	*token;

	token = malloc(sizeof(t_tokl));
	if (!token)
		return (NULL);
	token->con = con;
	token->type = type;
	token->next = NULL;
	return (token);
}

int	tok_add(t_tokl **tokl, t_tokl *token)
{
	t_tokl	*p;

	if (!token)
		return (0);
	if (!*tokl)
	{
		*tokl = token;
		return (1);
	}
	p = *tokl;
	while ((*tokl)->next)
		*tokl = (*tokl)->next;
	(*tokl)->next = token;
	*tokl = p;
	return (1);
}

void	tokl_delete(t_tokl **tokl)
{
	t_tokl	*p;

	while (*tokl)
	{
		p = *tokl;
		*tokl = (*tokl)->next;
		free(p->con);
		free(p);
	}
}

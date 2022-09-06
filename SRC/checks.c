/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkheiri <hkheiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 00:22:22 by hkheiri           #+#    #+#             */
/*   Updated: 2022/06/05 00:08:08 by hkheiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob_head.h"

int	check_nested(char *str)
{
	int		i;
	char	c;

	i = -1;
	while (str && str[++i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			c = str[i];
			while (str[++i] && str[i] != c)
				;
			if (!str[i])
			{
				printf("bash: doesn't support nested (\' or \" )\n");
				g_mini.exitst = 258;
				return (1);
			}
			c = 0;
		}
	}
	return (0);
}

int	check_it(t_tokl *tokl)
{
	t_tokl	*t;

	while (tokl)
	{
		t = tokl->next;
		if (isspectok(tokl) && t == NULL)
		{
			printf("bash: syntax error near unexpected token `%s'\n", tokl->con);
			g_mini.exitst = 258;
			return (1);
		}
		if (((isspectok(tokl) && isspectok(t)) && !(tokl->type == PIPET))
			|| ((tokl->type == PIPET) && (t->type == PIPET)))
		{
			printf("bash: syntax error near unexpected token `%s'\n", t->con);
			g_mini.exitst = 258;
			return (1);
		}
		tokl = tokl->next;
	}
	return (0);
}

int	check_from_tokl(t_tokl *tokl)
{
	t_tokl	*tok;

	tok = tokl;
	if (!tok)
		return (0);
	if ((isspectok(tok) && tok->next == NULL) || tok->type == PIPET)
	{
		printf("bash: syntax error near unexpected token `%s'\n", tok->con);
		g_mini.exitst = 258;
		return (1);
	}
	if (check_it(tokl))
		return (1);
	return (0);
}

void	sighandler(int sig)
{
	if (sig == SIGINT)
	{
		printf("MiniShell:\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

t_tokl	*tokl_from_str(char *string)
{
	t_tokl	*tokl;
	int		r_val;
	char	*p;

	tokl = NULL;
	p = string;
	r_val = tok_add(&tokl, get_next_char_tok(&p));
	while (r_val)
		r_val = tok_add(&tokl, get_next_char_tok(&p));
	return (tokl);
}

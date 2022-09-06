/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkheiri <hkheiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 00:33:41 by hkheiri           #+#    #+#             */
/*   Updated: 2022/06/05 00:33:41 by hkheiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob_head.h"

t_tokl	*get_spec_token(char **str)
{
	if (**str == '|')
		return (tok_init(ft_strdup("|"), PIPET));
	if (!strncmp(*str, ">>", (size_t) 2))
		return (tok_init(ft_strdup(">>"), RAP));
	if (!strncmp(*str, ">", (size_t) 1))
		return (tok_init(ft_strdup(">"), ROUT));
	if (!strncmp(*str, "<<", (size_t) 2))
		return (tok_init(ft_strdup("<<"), HD));
	if (!strncmp(*str, "<", (size_t) 1))
		return (tok_init(ft_strdup("<"), RIN));
	else
		return (NULL);
}

t_tokl	*get_next_char_tok(char **str)
{
	t_tokl	*r_token;

	r_token = NULL;
	if (!*str)
		return (NULL);
	if (!(**str))
		return (NULL);
	while (**str && iswhite(**str))
		(*str)++;
	if (**str && isspec(**str))
	{
		if (**str && ispre(**str))
		{
			r_token = get_pre(str);
			(*str)++;
		}
		else
		{
			r_token = get_spec_token(str);
			(*str) += strlen(r_token->con);
		}
	}
	else if (**str)
		r_token = get_del(str);
	return (r_token);
}

int	execute_from_str(char **env, char *str)
{
	t_tokl	*tokl;
	t_cmdl	*cmdl;
	char	*str_rep;

	if (check_nested(str))
		return (1);
	str_rep = replace_env_var(str, env);
	tokl = tokl_from_str(str_rep);
	free(str_rep);
	if (check_from_tokl(tokl))
	{
		tokl_delete(&tokl);
		return (1);
	}
	cmdl = cmdl_from_tokl(tokl);
	tokl_delete(&tokl);
	if (cmdl && !cmdl->next && is_builtin(cmdl))
		exec_builtin(&cmdl, 0);
	else
		execute(cmdl, env);
	cmdl_delete(&cmdl);
	return (1);
}

int	main(int ac, char **av, char **env)
{
	char	*buff;

	if (!ac || !env || !av)
		return (1);
	handle_echoctl();
	g_mini.exitst = 0;
	g_mini.env = dup_env(env);
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, sighandler);
		buff = readline("MiniShell: ");
		if (!buff)
		{
			free(buff);
			ft_putstr_fd("exit", 1);
			free_strs(g_mini.env, 0);
			exit(0);
		}
		add_history(buff);
		execute_from_str(g_mini.env, buff);
		free(buff);
	}
	return (0);
}

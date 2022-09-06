/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkheiri <hkheiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 00:03:48 by hkheiri           #+#    #+#             */
/*   Updated: 2022/05/26 00:11:24 by hkheiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob_head.h"

t_cmdl	*cmd_init(void)
{
	t_cmdl	*cmd;

	cmd = malloc(sizeof(t_cmdl));
	if (!cmd)
		return (NULL);
	cmd->outflag = TRUN;
	cmd->filein = NULL;
	cmd->fileout = NULL;
	cmd->next = NULL;
	cmd->cmdf = NULL;
	return (cmd);
}

void	cmdl_from_tokl_handler(t_tokl **tokl, t_cmdl *cmd)
{
	if ((*tokl) && !isspectok(*tokl))
		get_cmd_filel(&cmd->cmdf, tokl);
	else if ((*tokl) && (*tokl)->type == RIN)
		filel_add(&cmd->filein, get_word(tokl));
	else if ((*tokl) && (*tokl)->type == ROUT)
	{
		filel_add(&cmd->fileout, get_word(tokl));
		cmd->outflag = TRUN;
	}
	else if ((*tokl) && (*tokl)->type == HD)
		handle_heredoc(&cmd, tokl);
	else if ((*tokl) && (*tokl)->type == RAP)
	{
		filel_add(&cmd->fileout, get_word(tokl));
		cmd->outflag = APP;
	}
}

t_cmdl	*next_cmdl_from_tokl(t_tokl **tokl)
{
	t_cmdl	*cmd;

	if (!(*tokl))
		return (NULL);
	cmd = cmd_init();
	if ((*tokl) && (*tokl)->type == PIPET)
		(*tokl) = (*tokl)->next;
	while (*tokl)
	{
		cmdl_from_tokl_handler(tokl, cmd);
		if ((*tokl) && (*tokl)->type == PIPET)
			break ;
	}
	return (cmd);
}

int	cmdl_add(t_cmdl **cmdl, t_cmdl *cmd)
{
	t_cmdl	*p;

	if (!cmd)
		return (0);
	if (!(*cmdl))
	{
		*cmdl = cmd;
		return (1);
	}
	p = *cmdl;
	while ((*cmdl)->next)
		(*cmdl) = (*cmdl)->next;
	(*cmdl)->next = cmd;
	*cmdl = p;
	return (1);
}

void	cmdl_delete(t_cmdl **cmdl)
{
	t_cmdl	*p;

	while (*cmdl)
	{
		p = (*cmdl)->next;
		filel_delete(&(*cmdl)->filein);
		(*cmdl)->filein = NULL;
		filel_delete(&(*cmdl)->fileout);
		(*cmdl)->fileout = NULL;
		filel_delete(&(*cmdl)->cmdf);
		free((*cmdl));
		(*cmdl) = p;
	}
	p = NULL;
	(*cmdl) = NULL;
}

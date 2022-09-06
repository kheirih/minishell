/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkheiri <hkheiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 00:11:23 by hkheiri           #+#    #+#             */
/*   Updated: 2022/06/15 23:41:03 by hkheiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob_head.h"

char	**get_paths(char **env)
{
	int		i;
	char	**paths;

	i = -1;
	while (env[++i])
	{	
		if (ft_strnstr(env[i], "PATH=", 5))
			break ;
	}
	if (env[i] == NULL)
		return (NULL);
	paths = ft_split(env[i] + 5, ':');
	return (paths);
}

char	*get_cmd_path(char **paths, char *cmd)
{
	int		i;
	char	*rtn;
	int		rtn_len;
	int		access_rtn;

	i = -1;
	if (!cmd[0])
		return (NULL);
	while (paths && paths[++i])
	{
		rtn_len = ft_strlen(paths[i]) + ft_strlen(cmd) + 2;
		rtn = ft_calloc(rtn_len, sizeof(char ));
		ft_strlcat(rtn, paths[i], rtn_len);
		ft_strlcat(rtn, "/", rtn_len);
		ft_strlcat(rtn, cmd, rtn_len);
		access_rtn = access(rtn, F_OK | X_OK);
		if (access_rtn == 0)
			return (rtn);
		free(rtn);
		rtn = NULL;
	}
	access_rtn = access(cmd, F_OK | X_OK);
	if (access_rtn == 0)
		return (ft_strdup(cmd));
	return (NULL);
}

char	*get_cmd(char **env, char *cmd, int *fd)
{
	char	**paths;
	char	*cmd_path;

	paths = get_paths(env);
	cmd_path = get_cmd_path(paths, cmd);
	free_strs(paths, 0);
	if (!cmd_path)
	{
		printf("MiniShell: %s: No such file or directory\n", cmd);
		close(fd[1]);
		close(fd[0]);
		exit(127);
	}	
	return (cmd_path);
}

void	child_handler(int in, t_cmdl *cmd, int *pi, char **env)
{
	char	*cmd_na;
	t_cmdl	**cmdp;

	cmdp = &cmd;
	cmd_na = NULL;
	if (cmd->cmdf)
		cmd_na = get_cmd(env, cmd->cmdf->file_n, pi);
	if (in != 0)
	{
		dup2(in, 0);
		close(in);
	}
	if (cmd->next)
	{
		dup2(pi[1], 1);
		close(pi[1]);
	}
	close(pi[0]);
	if (open_cmdfin(cmd) || open_cmdfout(cmd))
		exit(errno);
	if (cmd_na && is_builtin(cmd))
		exec_builtin(cmdp, 1);
	else if (cmd->cmdf && cmd_na)
		ft_execve(cmd_na, cmd, filel_av(cmd->cmdf), env);
}

void	execute(t_cmdl *cmd, char **env)
{
	int		pi[2];
	int		in;
	int		st;

	in = STDIN_FILENO;
	while (cmd)
	{
		pipe(pi);
		if (!ft_fork())
		{
			signal(SIGQUIT, SIG_DFL);
			signal(SIGINT, SIG_DFL);
			child_handler(in, cmd, pi, env);
			exit(errno);
		}
		else
		{
			close(pi[1]);
			if (in)
				close(in);
			in = pi[0];
			cmd = cmd->next;
		}
	}
	exec_part(in, &st);
}

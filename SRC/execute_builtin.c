/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkheiri <hkheiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 23:17:48 by hkheiri           #+#    #+#             */
/*   Updated: 2022/06/05 04:59:09 by hkheiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob_head.h"

int	is_builtin(t_cmdl *cmd)
{
	if (!cmd->cmdf || !cmd->cmdf->file_n)
		return (0);
	if (!strcmp(cmd->cmdf->file_n, "echo"))
		return (1);
	if (!strcmp(cmd->cmdf->file_n, "cd"))
		return (2);
	if (!strcmp(cmd->cmdf->file_n, "exit"))
		return (3);
	else if (!strcmp(cmd->cmdf->file_n, "pwd"))
		return (4);
	if (!strcmp(cmd->cmdf->file_n, "unset"))
		return (5);
	else if (!strcmp(cmd->cmdf->file_n, "export"))
		return (6);
	else if (!strcmp(cmd->cmdf->file_n, "env"))
		return (7);
	return (0);
}

void	exec_by_index(t_cmdl **cmd, int f, int i)
{
	if (i == 1)
		ft_echo(filel_av((*cmd)->cmdf), f);
	else if (i == 4)
		ft_pwd(f);
	else if (i == 7)
		ft_env(filel_av((*cmd)->cmdf), f);
	else if (i == 6)
		ft_export(filel_av((*cmd)->cmdf), f);
	else if (i == 5)
		ft_unset(filel_av((*cmd)->cmdf), f);
	else if (i == 2)
		ft_cd(filel_av((*cmd)->cmdf), f);
	else if (i == 3)
		ft_exit(filel_av((*cmd)->cmdf), cmd);
}

void	exec_builtin(t_cmdl **cmd, int f)
{
	int	old_stds[2];

	if (!f)
	{
		old_stds[0] = dup(STDIN_FILENO);
		old_stds[1] = dup(STDOUT_FILENO);
	}
	if (open_cmdfin(*cmd) || open_cmdfout(*cmd))
		return ;
	exec_by_index(cmd, f, is_builtin(*cmd));
	if (!f)
	{
		dup2(old_stds[0], STDIN_FILENO);
		dup2(old_stds[1], STDOUT_FILENO);
	}
}

int	handle_echoctl(void)
{
	struct termios	config;
	int				fd ;

	fd = open(ttyname(STDIN_FILENO), O_RDWR | O_NOCTTY | O_NDELAY);
	if (tcgetattr(STDIN_FILENO, &config) < 0)
		return (0);
	config.c_lflag &= ~(ECHOCTL);
	if (tcsetattr(fd, TCSAFLUSH, &config) < 0)
		return (0);
	close(fd);
	return (1);
}

void	ft_execve(char *cmd_na, t_cmdl *cmd, char **av, char **env)
{
	execve(cmd_na, av, env);
	write(1, "MiniShell: ", strlen("MiniShell: "));
	ft_putstr_fd(cmd->cmdf->file_n, 1);
	perror(" ");
	exit(errno);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_filel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkheiri <hkheiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 23:56:37 by hkheiri           #+#    #+#             */
/*   Updated: 2022/06/05 04:52:34 by hkheiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob_head.h"
#include "libft.h"

int	open_cmdfin(t_cmdl *cmdl)
{
	int		fd;
	t_filel	*filein;

	filein = cmdl->filein;
	if (!filein)
		return (0);
	while (filein)
	{
		fd = open(filein->file_n, O_RDONLY);
		if (fd == -1)
		{
			write(1, "MiniShell: ", strlen("MiniShell: "));
			ft_putstr_fd(filein->file_n, 1);
			perror(" ");
			g_mini.exitst = errno;
			return (1);
		}
		if (filein->next)
			close(fd);
		filein = filein->next;
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

void	open_with_flag(t_cmdl *cmdl, t_filel *fileout, int *fd)
{
	if (cmdl->outflag == APP)
		*fd = open(fileout->file_n, O_CREAT | O_WRONLY | O_APPEND, 0666);
	else
		*fd = open(fileout->file_n, O_CREAT | O_WRONLY | O_TRUNC, 0666);
}

int	open_cmdfout(t_cmdl *cmdl)
{
	int		fd;
	t_filel	*fileout;

	fileout = cmdl->fileout;
	if (!fileout)
		return (0);
	while (fileout)
	{
		open_with_flag(cmdl, fileout, &fd);
		if (fd == -1)
		{
			write(1, "MiniShell: ", strlen("MiniShell: "));
			ft_putstr_fd(fileout->file_n, 1);
			perror(" ");
			g_mini.exitst = errno;
			return (1);
		}
		if (fileout->next)
			close(fd);
		fileout = fileout->next;
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	ft_fork(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		write(1, "MiniShell: ", strlen("MiniShell: "));
		perror(" ");
		exit(errno);
	}
	return (pid);
}

void	exec_part(int in, int *st)
{
	signal(SIGINT, SIG_IGN);
	if (in)
		close (in);
	while (waitpid(-1, st, 0) > 0)
		g_mini.exitst = WEXITSTATUS(*st);
}

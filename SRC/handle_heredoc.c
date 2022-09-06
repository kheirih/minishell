/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkheiri <hkheiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 03:25:55 by hkheiri           #+#    #+#             */
/*   Updated: 2022/06/08 00:59:00 by hkheiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob_head.h"

int	nbr_len(int n)
{
	int	i;
	int	sign;

	i = 0;
	sign = 0;
	if (n <= 0)
		sign = 1;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i + sign);
}

char	*here_open(char *temp_n, int i, int *fd)
{
	char		*index;

	index = ft_itoa(i);
	if (!index)
		return (NULL);
	strcat(temp_n, "/tmp/heredoc");
	strncat(temp_n, index, nbr_len(i));
	*fd = open(temp_n, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (*fd == -1)
	{
		perror("");
		free(index);
		return (NULL);
	}
	free(index);
	return (temp_n);
}

int	handle_heredoc_part(char **temp_name, int i,
	int *fd, t_filel **heredoc)
{
	char	*buff;
	int		rtn;

	here_open(*temp_name, i, fd);
	signal(SIGINT, SIG_IGN);
	if (!ft_fork())
	{
		signal(SIGINT, sighere);
		while (1)
		{
			buff = readline("> ");
			if (!buff || !strcmp(buff, (*heredoc)->file_n))
			{
				close(*fd);
				break ;
			}
			write(*fd, buff, strlen(buff));
			write(*fd, "\n", 1);
			free(buff);
			buff = NULL;
		}
		exit(0);
	}
	waitpid(-1, &rtn, 0);
	return (WEXITSTATUS(rtn));
}

char	*handle_heredoc(t_cmdl **cmd, t_tokl **tokl)
{
	t_filel		*heredoc;
	char		*temp_name;
	static int	i;
	int			fd;
	int			rtn;

	fd = 0;
	heredoc = get_word(tokl);
	temp_name = malloc(sizeof(char ) * (12 + nbr_len(i) + 1));
	temp_name[0] = 0;
	rtn = handle_heredoc_part(&temp_name, i, &fd, &heredoc);
	if (rtn)
	{
		fd = open(temp_name, O_WRONLY | O_TRUNC);
		close(fd);
	}
	g_mini.exitst = rtn;
	filel_delete(&heredoc);
	filel_add(&(*cmd)->filein, filel_init(temp_name));
	free(temp_name);
	i++;
	signal(SIGINT, sighandler);
	return (temp_name);
}

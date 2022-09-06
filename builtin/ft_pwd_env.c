/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rezzahra <rezzahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 18:23:50 by mac               #+#    #+#             */
/*   Updated: 2022/05/26 00:48:58 by rezzahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob_head.h"

void	putendl_fd(char *str, int fd)
{
	write(fd, str, ft_strlen(str));
	write(fd, "\n", 1);
}

void	ft_env(char **args, int f)
{
	char	**tmp;

	(void )args;
	if (args && args[1])
	{
		printf("env: %s: No such file or directory\n", args[1]);
		if (!f)
		{
			g_mini.exitst = 127;
			return ;
		}
		else
			exit(127);
	}
	tmp = g_mini.env;
	while (tmp && *tmp)
		printf("%s\n", *(tmp++));
	free_strs(args, 0);
	if (!f)
		g_mini.exitst = 0;
	else
		exit(0);
}

void	ft_pwd(int f)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd)
		putendl_fd(pwd, 1);
	else
	{
		if (get_var(g_mini.env, "PWD") != NULL)
			putendl_fd(get_var(g_mini.env, "PWD"), 1);
	}
	free(pwd);
	if (!f)
		g_mini.exitst = 0;
	else
		exit(0);
}

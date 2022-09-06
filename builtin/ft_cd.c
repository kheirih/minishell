/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkheiri <hkheiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 04:21:32 by hkheiri           #+#    #+#             */
/*   Updated: 2022/06/16 01:38:34 by hkheiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob_head.h"

void	ft_cd_part(char **pwd)
{
	*pwd = getcwd(NULL, 0);
	if (get_var(g_mini.env, "OLDPWD"))
	{
		printf("%s\n", get_var(g_mini.env, "OLDPWD"));
		chdir(get_var(g_mini.env, "OLDPWD"));
		env_add("OLDPWD", *pwd, &g_mini.env);
	}
	free(*pwd);
}

void	ft_cd_part_2(char **args)
{
	g_mini.exitst = WEXITSTATUS(errno);
	printf("MiniShel: cd: %s: No such file or directory\n", args[1]);
}

void	ft_cd(char **args, int f)
{
	char	*pwd;

	g_mini.exitst = 0;
	if (args[1] == NULL)
	{
		if (get_var(g_mini.env, "HOME") != NULL)
			chdir(get_var(g_mini.env, "HOME"));
		else
			printf("MiniShell: cd: HOME not set\n");
	}
	else if (args[1][0] == '-' && args[1][1] == '\0')
		ft_cd_part(&pwd);
	else if (args[1][0] == '~')
		chdir((const char *)get_var(g_mini.env, "HOME"));
	else if (args[1][0] == '.' && args[1][1] == '\0')
		chdir(get_var(g_mini.env, "PWD"));
	else
	{
		if (chdir(args[1]) == -1)
			ft_cd_part_2(args);
		free_strs(args, 0);
		if (f)
			exit(g_mini.exitst);
	}
}

int	spec_case(char **str, int *i)
{
	if (iswhite((*str)[*i + 1]) || !(*str)[*i + 1] || (*str)[*i + 1] == '$' ||
		(*str)[*i + 1] == '\"')
		return (1);
	return (0);
}

void	sighere(int i)
{
	if (i == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		exit(1);
	}
}

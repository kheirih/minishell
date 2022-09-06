/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkheiri <hkheiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 04:52:16 by hkheiri           #+#    #+#             */
/*   Updated: 2022/06/07 23:43:50 by hkheiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob_head.h"

int	lenarr(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return (1);
	while (arr[i])
		i++;
	return (i);
}

void	exit_cases(char **args)
{
	if (lenarr(args) == 1)
	{
		printf("exit\n");
		g_mini.exitst = 0;
	}
	else if ((lenarr(args) == 2) && isalldigit(args[1]))
	{
		printf("exit\n");
		g_mini.exitst = ft_atoi(args[1]) % 256;
	}
	else if (!isalldigit(args[1]))
	{
		printf("exit\n");
		printf("exit: %s numeric argument required\n", args[1]);
	}
	else if (lenarr(args) > 2)
	{
		printf("exit\n");
		printf("exit: too many arguments\n");
	}
}

void	ft_exit(char **args, t_cmdl **cmdl)
{
	int	i;

	i = 0;
	g_mini.exitst = 255;
	exit_cases(args);
	free_strs(g_mini.env, 0);
	if (cmdl)
		cmdl_delete(cmdl);
	free_strs(args, 0);
	exit(g_mini.exitst);
}

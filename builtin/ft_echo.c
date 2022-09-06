/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkheiri <hkheiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 13:20:04 by mac               #+#    #+#             */
/*   Updated: 2022/06/16 01:59:20 by hkheiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob_head.h"

void	putstr_fd_flag(char *str, int fd, int flag)
{
	while (*str)
	{
		if (flag == 1)
		{
			if (*str == '\n')
				str++;
			else
				write(1, str, fd);
		}
		else
			write(1, str, fd);
		str++;
	}
}

int	rep_n(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '-' || !str[i + 1])
		return (0);
	while (str && str[++i])
	{
		if (str[i] != 'n')
			return (0);
	}
	return (1);
}

void	ft_echo(char **args, int f)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	while (args[i] && rep_n(args[i]))
	{
		flag = 1;
		i++;
	}
	while (args[i])
	{
		putstr_fd_flag(args[i], 1, flag);
		if (args[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
	free_strs(args, 0);
	if (flag != 1)
		write(1, "\n", 1);
	if (f)
		exit(0);
	g_mini.exitst = 0;
}

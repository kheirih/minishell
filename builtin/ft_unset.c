/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkheiri <hkheiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 03:43:31 by hkheiri           #+#    #+#             */
/*   Updated: 2022/06/05 05:47:42 by hkheiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob_head.h"

void	delete_var(char ***env, char *var)
{
	int		i;
	char	**r_env;
	int		j;

	i = 0;
	j = 0;
	r_env = malloc(sizeof(char *) * (env_len(*env)));
	while ((*env)[i])
	{
		if (strncmp((*env)[i], var, ft_strlen(var)) != 0)
		{
			r_env[j] = ft_strdup((*env)[i]);
			j++;
		}
		i++;
	}
	r_env[j] = 0;
	free_strs(*env, 0);
	*env = r_env;
}

void	ft_unset(char **args, int f)
{
	char	*key;
	char	**tmp;

	g_mini.exitst = 0;
	tmp = args++;
	while (*args)
	{
		key = get_var(g_mini.env, *args);
		if (!key)
		{
			args++;
			continue ;
		}
		else if (isvalid(*args))
			delete_var(&g_mini.env, *args);
		else
		{
			printf(" unset: '%s': not a valid identifier\n", *args);
			g_mini.exitst = 1;
		}
		args++;
	}
	free_strs(tmp, 0);
	if (f)
		exit(g_mini.exitst);
}

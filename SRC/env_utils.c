/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rezzahra <rezzahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 22:24:37 by hkheiri           #+#    #+#             */
/*   Updated: 2022/05/26 00:57:55 by rezzahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob_head.h"

int	env_len(char **env)
{
	int	i;

	i = -1;
	while (env && env[++i])
		;
	return (i);
}

char	**dup_env(char **env)
{
	int		i;
	char	**r_env;

	i = -1;
	r_env = malloc(sizeof(char *) * (env_len(env) + 1));
	while (env[++i])
		r_env[i] = strdup(env[i]);
	r_env[i] = 0;
	return (r_env);
}

int	env_modi(char *key, char *key_val, char ***env)
{
	int		i;
	char	*k;

	k = malloc(strlen(key) + 2);
	if (!k)
		return (0);
	*k = 0;
	strcat(k, key);
	strcat(k, "=");
	i = -1;
	while (strncmp((*env)[++i], k, strlen(k)))
		;
	free((*env)[i]);
	(*env)[i] = malloc(strlen(k) + strlen(key_val) + 1);
	if (!(*env)[i])
	{
		free(k);
		return (0);
	}
	(*env)[i][0] = 0;
	strcat((*env)[i], k);
	strcat((*env)[i], key_val);
	free(k);
	return (1);
}

int	env_add(char *key, char *key_val, char ***env)
{
	int		len;
	char	**r_env;
	int		i;
	char	*r_var;

	r_var = get_var(*env, key);
	if (r_var)
	{
		env_modi(key, key_val, env);
		return (1);
	}
	len = env_len(*env);
	r_env = malloc(sizeof(char *) * (len + 2));
	i = -1;
	while ((*env)[++i])
		r_env[i] = strdup((*env)[i]);
	r_env[i] = malloc(sizeof(char *) * (strlen(key) + strlen(key_val) + 2));
	r_env[i][0] = 0;
	strcat(r_env[i], key);
	strcat(r_env[i], "=");
	strcat(r_env[i], key_val);
	r_env[i + 1] = 0;
	free_strs(*env, 0);
	*env = r_env;
	return (1);
}

t_cmdl	*cmdl_from_tokl(t_tokl *tokl)
{
	t_cmdl	*cmdl;
	int		r_val;

	cmdl = NULL;
	r_val = cmdl_add(&cmdl, next_cmdl_from_tokl(&tokl));
	while (r_val)
		r_val = cmdl_add(&cmdl, next_cmdl_from_tokl(&tokl));
	return (cmdl);
}

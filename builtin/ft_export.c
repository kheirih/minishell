/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rezzahra <rezzahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 18:02:55 by rezzahra          #+#    #+#             */
/*   Updated: 2022/05/26 00:48:47 by rezzahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob_head.h"

char	**sortstr(char ***str)
{
	char	**arr;
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	arr = *str;
	while (i < env_len(*str))
	{
		j = 0;
		while (j < env_len(*str) - i - 1)
		{
			if (strcmp(arr[j], arr[j + 1]) > 0)
			{
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
	return (arr);
}

int	isalldigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	isvalid(char *arg)
{
	if (isalldigit(arg))
		return (0);
	while (*arg)
	{
		if (*arg != '_' && !ft_isalpha(*arg) && !ft_isdigit(*arg))
			return (0);
		arg += 1;
	}
	return (1);
}

void	exporting(char **args, char *key)
{
	while (*args)
	{	
		key = ft_substr(*args, 0, ft_strchr(*args, '=') - *args);
		if (isvalid(key))
		{	
			if (ft_strchr(*args, '='))
				env_add(key, ft_strchr(*args, '=') + 1, &g_mini.env);
			else if (ft_strchr(*args, '=')
				&& (*args)[ft_strlen(*args) - 1] == '=')
				env_add(*args, "", &g_mini.env);
		}
		else
		{
			printf("export: `%s': not a valid identifier\n", key);
			g_mini.exitst = 1;
		}
		free(key);
		args++;
	}
}

void	ft_export(char **args, int f)
{
	char	**argst;
	char	**tmp;
	char	**arr;
	char	*key;

	key = NULL;
	argst = args;
	tmp = NULL;
	g_mini.exitst = 0;
	if (env_len(args) == 1 && !args[1])
	{
		tmp = dup_env(g_mini.env);
		arr = sortstr(&tmp);
		while (*arr)
			printf("declare -x %s\n",*arr++);
		free_strs(tmp, 0);
	}
	else
		exporting(args, key);
	if (argst)
		free_strs(argst, 0);
	if (!f)
		return ;
	else
		exit(g_mini.exitst);
}

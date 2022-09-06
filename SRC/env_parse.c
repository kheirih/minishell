/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkheiri <hkheiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 03:25:30 by hkheiri           #+#    #+#             */
/*   Updated: 2022/06/16 01:44:07 by hkheiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob_head.h"

char	*get_var(char **env, char *key)
{
	int		i;
	char	*k;
	int		len;

	i = 0;
	k = malloc(sizeof(char) * (strlen(key) + 2));
	if (!k)
		return (NULL);
	*k = 0;
	len = strlen(key) + 1;
	strncat(k, key, strlen(key) + 1);
	strcat(k, "=");
	while (env[i])
	{
		if (strncmp(env[i], k, len) == 0)
		{
			free(k);
			return (env[i] + len);
		}
		i++;
	}
	free(k);
	return (NULL);
}

void	replace_env_part(char *r_str, char **str, int *i, t_vars *v)
{
	r_str[0] = 0;
	strncat(r_str, (*str), *i);
	strncat(r_str, v->key_value, strlen(v->key_value));
	strncat(r_str, *str + *i + strlen(v->key) + 1,
		strlen(*str + *i + strlen(v->key) + 1));
	*i += strlen(v->key_value);
}

char	*replace_env(char **str, int *i, char **env)
{
	int		s;
	char	*r_str;
	t_vars	v;

	v.key_value = 0;
	s = *i;
	while ((*str)[++s] && (*str)[s] != '$' && !iswhite((*str)[s])
		&& !ispre((*str)[s]))
		;
	v.key = malloc(sizeof(char ) * (s - *i + 1));
	v.key[0] = 0;
	strncat(v.key, &(*str)[*i + 1], s - *i - 1);
	if (spec_case(str, i))
		v.key_value = strdup("$");
	else
		v.key_value = get_var(env, v.key);
	if (!v.key_value)
		v.key_value = strdup("");
	r_str = malloc(sizeof(char) * (strlen((*str))
				- strlen(v.key) + strlen(v.key_value)));
	replace_env_part(r_str, str, i, &v);
	free(v.key);
	free(*str);
	*str = r_str;
	return (r_str);
}

int	ques_case(char **str, int *i)
{
	t_vars	v;
	char	key[2];
	char	*r_str;

	key[0] = '?';
	key[1] = 0;
	v.key = key;
	v.key_value = ft_itoa(g_mini.exitst);
	if (!(*str)[*i + 1] || (*str)[*i + 1] != '?')
		return (0);
	r_str = malloc(sizeof(char) * (strlen((*str)) - 1
				+ strlen(v.key_value) + 1));
	replace_env_part(r_str, str, i, &v);
	free(*str);
	*str = r_str;
	return (1);
}

char	*replace_env_var(char *str, char **env)
{
	int		i;
	char	*r_str;

	i = 0;
	if (!str)
		return (NULL);
	r_str = strdup(str);
	while (r_str && r_str[i])
	{
		if (r_str[i] == '\'' )
		{
			while (r_str[++i] != '\'' && r_str[i])
				;
			continue ;
		}
		else if (r_str[i] == '$')
		{
			if (ques_case(&r_str, &i))
				continue ;
			replace_env(&r_str, &i, env);
		}
		else
			i++;
	}
	return (r_str);
}

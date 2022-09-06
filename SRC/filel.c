/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rezzahra <rezzahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 23:39:02 by hkheiri           #+#    #+#             */
/*   Updated: 2022/05/26 00:52:02 by rezzahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob_head.h"

t_filel	*filel_init(char *file_n)
{
	t_filel	*filel;

	if (!file_n)
		return (NULL);
	filel = malloc(sizeof(t_filel));
	if (!filel)
		return (NULL);
	filel->file_n = strdup(file_n);
	filel->next = NULL;
	return (filel);
}

int	filel_add(t_filel **filel, t_filel *file)
{
	t_filel	*p;

	if (!file)
		return (0);
	if (!(*filel))
	{
		(*filel) = file;
		return (1);
	}
	p = *filel;
	while ((*filel)->next)
		*filel = (*filel)->next;
	(*filel)->next = file;
	*filel = p;
	return (1);
}

void	filel_delete(t_filel **filel)
{
	t_filel	*p;

	if (!(*filel))
		return ;
	while (*filel)
	{
		p = *filel;
		*filel = (*filel)->next;
		free(p->file_n);
		p->file_n = NULL;
		free(p);
		p = NULL;
	}
	(*filel) = NULL;
}

int	filel_size(t_filel *lst)
{
	int		i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

char	**filel_av(t_filel *cmdf)
{
	char	**arr;
	int		i;

	i = 0;
	arr = (char **)malloc(sizeof(char *) * (filel_size(cmdf) + 1));
	while (cmdf)
	{
		arr[i] = ft_strdup(cmdf->file_n);
		cmdf = cmdf->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

// void check(int ac, char **av)
// {
// 	int i = -1;
// 	t_filel *filel = NULL;
// 	t_filel *p;
// 	if (!ac)
// 		return ;
// 	while(av[++i])
// 		filel_add(&filel, filel_init(av[i]));
// 	i = -1;

// 	p = filel;
// 	while (p)
// 	{
// 		printf("{%s}  ", p->file_n);
// 		p = p->next;
// 	}
// 	filel_delete(&filel);
// }

// int main(int ac, char *av[]){
// 	check(ac, av);
// 	while(1);
// }
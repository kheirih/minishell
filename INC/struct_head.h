/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_head.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkheiri <hkheiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 22:40:54 by rezzahra          #+#    #+#             */
/*   Updated: 2022/06/02 03:41:11 by hkheiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_HEAD_H
# define STRUCT_HEAD_H

typedef struct s_filel
{
	char			*file_n;
	struct s_filel	*next;
}				t_filel;

typedef struct s_cmdl
{
	int				outflag;
	t_filel			*filein;
	t_filel			*fileout;
	t_filel			*cmdf;
	struct s_cmdl	*next;
}	t_cmdl;

typedef struct s_tokl
{
	char			*con;
	int				type;
	struct s_tokl	*next;
}				t_tokl;

typedef struct s_min
{
	char	**env;
	int		exitst;
}				t_min;

typedef struct s_vars
{
	char	*key;
	char	*key_value;
}				t_vars;

#endif
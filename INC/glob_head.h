/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_head.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkheiri <hkheiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 22:35:07 by rezzahra          #+#    #+#             */
/*   Updated: 2022/06/16 01:37:33 by hkheiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOB_HEAD_H

# define GLOB_HEAD_H
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <unistd.h>
# include <signal.h>
# include <stdio.h>
# include "libft.h"
# include "struct_head.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <termios.h>
# include <sys/ioctl.h>
# define PIPET 0
# define WORD 1
# define RIN 2
# define ROUT 3
# define RAP 4
# define UQ 5
# define DQ 6
# define HD 7
# define PIPEIN 1
# define PIPEOUT 2
# define FILE_OUTP 3
# define TRUN 4
# define APP 5

char	*finder(char **env, char *cmd);
int		findstr(char **table);
int		ft_strcmp(char *s1, char *s2);
int		check_file_ex(char	*path);
int		outputshandler(t_filel *fileout);
int		inputshandler(t_filel *filein);
int		check_file_ex(char	*path);
int		check_file_ex1(char	*path);
t_filel	*filel_init(char *str);
int		filel_add(t_filel **filel, t_filel *file);
void	filel_delete(t_filel **filel);
int		filel_size(t_filel *lst);
char	**filel_av(t_filel *cmdf);
char	*ft_strdup(const char *s1);
t_tokl	*get_next_char_tok(char **str);
t_tokl	*tok_init(char *ct, int type);
void	tokl_delete(t_tokl **tokl);
int		tok_add(t_tokl **tokl, t_tokl *token);
int		strlen_p(char *str);
int		strlen_w(char *str);
int		ispre(char c);
int		iswhite(char c);
int		isspec(char c);
char	*get_var(char **env, char *key);
char	*replace_env_var(char *str, char **env);
t_tokl	*get_pre(char **str);
t_tokl	*get_del(char **str);

t_cmdl	*cmdl_from_tokl(t_tokl *tokl);
int		cmdl_add(t_cmdl **cmdl, t_cmdl *cmd);
t_cmdl	*next_cmdl_from_tokl(t_tokl **tokl);
t_cmdl	*cmd_init(void);
int		isspectok(t_tokl *t);
char	**get_cmd_av(t_tokl **tokl);
t_filel	*get_word(t_tokl **tokl);
void	free_strs(char **str, int in);
void	cmdl_delete(t_cmdl **cmdl);
int		get_cmd_filel(t_filel **cmdf, t_tokl **tokl);
char	*handle_heredoc(t_cmdl **cmd, t_tokl **tokl);
int		check_from_tokl(t_tokl *tokl);
int		check_nested(char *str);
int		env_add(char *key, char *key_val, char ***env);
char	**dup_env(char **env);
int		open_cmdfin(t_cmdl *cmdl);
int		open_cmdfout(t_cmdl *cmdl);
void	execute(t_cmdl *cmd, char **env);
int		nbr_len(int n);

int		is_builtin(t_cmdl *cmd);
void	exec_builtin(t_cmdl **cmd, int i);
void	ft_echo(char **args, int f);
void	ft_pwd(int f);
void	ft_env(char **args, int f);
void	ft_export(char **args, int f);
int		env_len(char **env);
void	ft_unset(char **args, int f);
int		isvalid(char *arg);
void	display_env(char **env);
void	ft_cd(char **args, int f);
void	ft_exit(char **args, t_cmdl **cmdl);
int		isalldigit(char *str);
void	sighandler(int sig);
t_tokl	*tokl_from_str(char *string);
int		ft_fork(void);
void	exec_part(int in, int *st);
t_min	g_mini;
int		handle_echoctl(void);
void	ft_execve(char *cmd_na, t_cmdl *cmd, char **av, char **env);
void	sighere(int i);
int		spec_case(char **str, int *i);
// void	sigquit(int i);
#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v0_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 13:06:36 by alienard          #+#    #+#             */
/*   Updated: 2020/06/14 14:15:55 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef V0_MINISHELL_H
# define V0_MINISHELL_H

#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <sys/errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include "libft/libft.h"
#include "libft/libftprintf.h"
#include "libft/libftdprintf.h"
#include "libft/libftfprintf.h"

# define SPACE " \t\r\n\v\f"

# define TOKENS "-\"\'|;><"

# define PROMPT "minishell$ "

# define QPROMPT "> "

# define BUILTINS &ft_exit, &ft_echo, &ft_pwd, &ft_env, &ft_change_dir//, &ft_export, &ft_unset

typedef struct	s_sh
{
	int	fd;
	int	check;
}				t_sh;

/*
typedef struct	s_env
{
	int	fd;
	int	check;
}				t_env;
*/

typedef struct	s_env
{
	char *key;
	char *value;
}				t_env;

int				ft_launch(char **args, char **env);

int			ft_parse_line(char *args, t_list *env, int (*builtin_fct[7])(char **, t_list *));

char		**ft_split_line(char **inputs);
char		**ft_split_quote(char *str, char c);

void		ft_prompt(int *check, int fd, t_list *env);
void		ft_check_line(char **line, int *quote);

int			ft_echo(char **args, t_list *env);
int			ft_exit(char **args, t_list *env);

void		ft_free_double_array(char **str);
void		ft_print_double_array(char **str, char *name);
size_t		ft_double_strlen(char **str);

char	*ft_lststrjoin(t_list *lst, char *inter);

char	*ft_parse_path(char *path);

char	*ft_lststrjoin(t_list *lst, char *inter);

int		ft_isolate_exec(char *path, char **buff);

int		ft_change_dir(char **args, t_list *env);

int		ft_env(char **args, t_list *env);

int		ft_pwd(char **args, t_list *env);

int		ft_export(char **args, char **env);

t_list	*ft_start_minishell(char **env);

t_list	*ft_split_to_lst_env(char **env);
void	ft_free_env_lst(void *env_lst);
void	ft_sort_env_lst(t_list *env_lst);
t_env	*ft_separate_key_value(char *env_str);

char	**ft_lst_env_to_split(t_list *lst_env);

# endif

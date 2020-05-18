/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v0_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 13:06:36 by alienard          #+#    #+#             */
/*   Updated: 2020/05/18 16:18:22 by cdai             ###   ########.fr       */
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
#include "libft/get_next_line_bonus.h"

# define SPACE " \t\r\n\v\f"

# define TOKENS "-\"\'|;><"

# define PROMPT "minishell$ "

# define QPROMPT "> "

# define BUILTINS &ft_echo, &ft_exit, &ft_change_dir, &ft_pwd, &ft_export, &ft_env //&ft_unset

typedef struct	s_sh
{
	int	fd;
	int	check;
}				t_sh;

typedef struct	s_env
{
	int	fd;
	int	check;
}				t_env;

typedef struct	s_minishell_data
{
	char	**av;
	char	**env;
}				t_minishell_data;

int				ft_launch(char **args, char **env);

int			ft_parse_line(char *args, char **env, int (*builtin_fct[7])(char **, char **));

char		**ft_split_line(char **inputs);
char		**ft_split_quote(char *str, char c);

void		ft_prompt(int *check, int fd, char **env);
void		ft_check_line(char **line, int *quote);

int			ft_echo(char **args, char **env);
int			ft_exit(char **args, char **env);

void		ft_free_double_array(char **str);
void		ft_print_double_array(char **str, char *name);
size_t		ft_double_strlen(char **str);

char	*ft_lststrjoin(t_list *lst, char *inter);

char	*ft_parse_path(char *path);

char	*ft_lststrjoin(t_list *lst, char *inter);

int		ft_isolate_exec(char *path, char **buff);

int		ft_change_dir(char **args, char **env);

int		ft_env(char **args, char **env);

int		ft_pwd(char **args, char **env);

int		ft_export(char **args, char **env);

char	**ft_start_minishell(char **env);

# endif

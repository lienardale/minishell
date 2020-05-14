/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v0_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 13:06:36 by alienard          #+#    #+#             */
/*   Updated: 2020/05/14 17:49:22 by alienard         ###   ########.fr       */
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

# define BUILTINS &ft_echo, &ft_exit// , &ft_cd, &ft_pwd, &ft_export, &ft_unset, &ft_env

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

int				ft_launch(char **args, char **env);

int			ft_parse_line(char *args, char **env, int (*builtin_fct[7])(char **));

char		**ft_split_line(char **inputs);
char		**ft_split_quote(char *str, char c);

void		ft_prompt(int *check, int fd, char **env);

int			ft_echo(char **args);
int			ft_exit(char **args);

# endif

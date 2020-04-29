/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v0_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 13:06:36 by alienard          #+#    #+#             */
/*   Updated: 2020/04/21 16:32:40 by alienard         ###   ########.fr       */
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
#include "libft/libft.h"
#include "libft/libftprintf.h"
#include "libft/libftdprintf.h"
#include "libft/libftfprintf.h"
#include "libft/get_next_line_bonus.h"

#include <string.h>

# define LSH_TOK_BUFSIZE 64
# define SPACE " \t\r\n\v\f"

typedef struct	s_sh
{
	int	fd;
	int	check;
}				t_sh;


int		lsh_cd(char **args, char **builtin_str);
int		lsh_help(char **args, char **builtin_str);
int		lsh_exit(char **args, char **builtin_str);
int		lsh_num_builtins(char **builtin_str);

int		lsh_launch(char **args);
int		lsh_execute(char **args);
char	**lsh_split_line(char *line);
char	*lsh_read_line(void);
void	lsh_loop(void);

# endif
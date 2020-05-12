/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v0_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 13:06:36 by alienard          #+#    #+#             */
/*   Updated: 2020/05/12 11:57:19 by cdai             ###   ########.fr       */
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

# define SPACE " \t\r\n\v\f"

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

int		ft_parse_line(char **args, char **env);

char	**ft_split_line(char *line);

void	ft_prompt(int *check, int fd, char **env);

char	*ft_lststrjoin(t_list *lst, char *inter);

char	*ft_parse_path(char *path);

# endif

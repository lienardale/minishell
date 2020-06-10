/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v0_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 11:19:02 by alienard          #+#    #+#             */
/*   Updated: 2020/06/10 11:05:48 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

int	ft_pipe_init(pid_t pid, int pfd[2], char *args, char **env, int (*builtin_fct[7])(char **, char **))
{
	int	ret;

	if (pid == 0)
	{
		/* child */
		close(pfd[1]); /* close the unused write side */
		dup2(pfd[0], STDIN_FILENO); /* connect the read side with stdin */
		close(pfd[0]); /* close the read side */
	}
	else
	{
		/* parent */
		close(pfd[0]); /* close the unused read side */
		dup2(pfd[1], STDOUT_FILENO); /* connect the write side with stdout */
		close(pfd[1]); /* close the write side */
	}
	ret = ft_parse_line(pid, pfd, args, env, builtin_fct);
	return (ret);
}

int	ft_pipe_split(char **args, char **env, int (*builtin_fct[7])(char **, char **))
{
	int		i;
	int		j;
	char	**tmp;
	int		ret;

	i = -1;
	while (args[++i])
	{
		tmp = ft_split_quote(args[i], '|');
		j = -1;
		while (tmp[++j])
			ret = ft_pipe(tmp[j], env, builtin_fct);
		ft_free_double_array(tmp);
	}
	ft_free_double_array(args);
	return (ret);
}

int	ft_pipe(char *args, char **env, int (*builtin_fct[7])(char **, char **))
{
	int		ret;
	/* create the pipe */
	int		pfd[2];
	pid_t	pid;

	if (pipe(pfd) == -1)
	{
		ft_dprintf(2, "pipe failed\n");
		return (1);
	}

	/* create the child */
	if ((pid = fork()) < 0)
	{
		ft_dprintf(2, "fork failed\n");
		return (2);
	}
	ret = ft_pipe_init(pid, pfd, args, env, builtin_fct);
	return (ret);
}

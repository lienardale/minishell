/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v0_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 08:12:21 by alienard          #+#    #+#             */
/*   Updated: 2020/06/10 17:23:52 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

int		ft_parse_line(pid_t pid, char *args, char **env, int (*builtin_fct[7])(char **, char **))
{
	char	**builtins;
	char	**arg;
	int		i;

/*
	in this function we do 3 things :
	1) split the char *args into a char ** that can be used by execve or the builtins fct, it is as follow
	2) compare the cmd to the buitins ones
	3) return either the corresponding builtin fct or the execve launching in ft_launch
*/

	// builtins = ft_split("echo,exit,cd,pwd,export,unset,env", ',');
	builtins = ft_split("echo,exit,cd,pwd,export,env", ',');
	// 1)
	arg = ft_split_quote(args, ' ');
	if (arg[0] == NULL)
	{
	// An empty command was entered.
		return (1);
	}

	i = -1;
	// 2)
	while (builtins[++i])
	{
		if (ft_strcmp(arg[0], builtins[i]) == 0)
		{
			ft_free_double_array(builtins);
			// 3)
			return (builtin_fct[i](arg, env));
		}
	}
	ft_free_double_array(builtins);
	// 3)
	return (ft_launch(pid, arg, env));
}

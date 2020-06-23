/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v0_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 08:12:21 by alienard          #+#    #+#             */
/*   Updated: 2020/06/23 15:06:10 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

int		ft_parse_cmds(t_cmd *cmd, t_sh *sh)
{
	char	**builtins;
	int		i;

	builtins = ft_split("exit,echo,pwd,env,cd,export,unset", ',');
	i = 0;
	// 1
	if (cmd->cmd == NULL)
	{
	// An empty command was entered.
		return (1);
	}
	i = -1;
	while (builtins[++i])
	{
		if (ft_strcmp(cmd->cmd, builtins[i]) == 0)
		{
			ft_free_double_array(builtins);
			return (sh->blt_fct[i](cmd->av, sh->env));
		}
	}
	ft_free_double_array(builtins);
	return (ft_launch(cmd->av, sh->env));
}

int		ft_parse_line(char *args, t_list **env, int (*builtin_fct[7])(char **, t_list **))
{
	char	**builtins;
	char	**arg;
	int		i;
	int		len;

/*
	in this function we do 3 things :
	1) split the char *args into a char ** that can be used by execve or the builtins fct, it is as follow
		arg[0] = cmd
		arg[1] = option / argument / null
		arg[2] = argument / null
		arg[3] = null
	2) compare the cmd to the buitins ones
	3) return either the corresponding builtin fct or the execve launching in ft_launch
*/

	// printf("arguments recus dans parse : |%s|\n", args);
	// builtins = ft_split("echo,exit,cd,pwd,export,unset,env", ',');
	builtins = ft_split("exit,echo,pwd,env,cd,export,unset", ',');
	len = -1;
	i = 0;
	// 1)
	arg = ft_split_quote(args, ' ');
	if (arg[0] == NULL)
	{
	// An empty command was entered.
		return (1);
	}
	i = -1;
	// printf("commande deduite : |%s|\n", arg[0]);
	// ft_print_double_array(arg, "arg de commande:");
	// 2)
	while (builtins[++i])
	{
		if (ft_strcmp(arg[0], builtins[i]) == 0)
		{
			ft_free_double_array(builtins);
			//printf("parse.c: %s\n", arg[0]);
			// 3)
			return (builtin_fct[i](arg, env));
		}
	}
	ft_free_double_array(builtins);
	// 3)
	return (ft_launch(arg, env));
//	return (1);
}

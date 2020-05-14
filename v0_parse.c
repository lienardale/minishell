/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v0_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 08:12:21 by alienard          #+#    #+#             */
/*   Updated: 2020/05/14 18:19:47 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

int		ft_parse_line(char *args, char **env, int (*builtin_fct[7])(char **))
{
	char	**builtins;
	char	**arg;
	int		i;
	int		len;

	printf("arguments recus dans parse : |%s|\n", args);
	// builtins = ft_split("echo,exit,cd,pwd,export,unset,env", ',');
	builtins = ft_split("echo,exit", ',');
	len = -1;
	i = 0;
	if (!(arg = ft_calloc(3, sizeof(char *))))
		return (1);
	args = ft_strtrim(args, SPACE);
	while (args[++len])
	{
		if (ft_isspace(args[len]))
			break ;
	}
	args[len] = '\0';
	arg[i++] = ft_strdup(args);
	if (args[++len])
		arg[i++] = ft_strdup(&args[len]);
	arg[i] = 0;
	if (arg[0] == NULL)
	{
	// An empty command was entered.
		return (1);
	}
	i = -1;
	printf("commande deduite : |%s|\n", arg[0]);
	while (builtins[++i])
	{
		if (ft_strcmp(arg[0], builtins[i]) == 0)
			return (builtin_fct[i](arg));
	}
	return (ft_launch(arg, env));
}

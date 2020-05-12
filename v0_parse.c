/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v0_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 08:12:21 by alienard          #+#    #+#             */
/*   Updated: 2020/05/12 18:48:58 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

int		ft_parse_line(char **args, char **env)
{
	if (args[0] == NULL)
	{
	// An empty command was entered.
		return (1);
	}
	else if (ft_strcmp(args[0], "pwd") == 0)
		return (ft_pwd());
	else if (ft_strcmp(args[0], "cd") == 0)
		return (ft_change_dir(args));
	else if (ft_strcmp(args[0], "env") == 0)
		return (ft_env(env));
	else if (ft_strcmp(args[0], "exit") == 0)
		return (0);
	return (ft_launch(args, env));
}

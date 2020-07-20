/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v0_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 08:12:21 by alienard          #+#    #+#             */
/*   Updated: 2020/07/20 11:44:10 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

int		ft_parse_cmds(t_cmd *cmd, t_sh *sh)
{
	char	**builtins;
	int		i;
	int		pipefd[2];

	if (pipe(pipefd) < 0)
	{
		ft_dprintf(2, "Pipe failed to initialize\n");
		return (2);
	}
	
	builtins = ft_split("exit,echo,pwd,env,cd,export,unset", ',');
	i = 0;
	
	if (cmd->cmd == NULL)
	{
		// ft_printf("An empty command was entered. : |%s|\n", cmd->cmd);
		// An empty command was entered.
		return (1);
	}
	i = -1;
	// printf("is into parse cmds | cmd:|%s|\n", (char*)cmd->cmd);
	while (builtins[++i])
	{
		if (ft_strcmp(cmd->cmd, builtins[i]) == 0)
		{
			ft_free_double_array(builtins);
			// printf("goes into builtins\n");
			return (sh->blt_fct[i](cmd, sh));
		}
	}
	ft_free_double_array(builtins);
	// printf("goes into launch\n");
	return (ft_launch(cmd, sh));
}

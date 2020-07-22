/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v0_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 08:12:21 by alienard          #+#    #+#             */
/*   Updated: 2020/07/22 15:30:11 by alienard         ###   ########.fr       */
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
	while (builtins[++i])
	{
		if (ft_strcmp(cmd->cmd, builtins[i]) == 0)
		{
			// if (cmd->redir)
			// {
			// 	if ((cmd->fdout = open(cmd->redir, O_WRONLY | O_CREAT | O_TRUNC, 0777)) == -1)
			// 	{
			// 		ft_dprintf(2, "Error in open.\n");
			// 		return (0);
			// 	}
			// 	if ((cmd->ret_dup = dup2(cmd->fdout, STDOUT_FILENO)) == -1)
			// 		ft_exit((t_cmd*)(sh->cmds->head), sh);
			// }
			ft_free_double_array(builtins);
			return (sh->blt_fct[i](cmd, sh));
		}
	}
	ft_free_double_array(builtins);
	return (ft_launch(cmd, sh));
}

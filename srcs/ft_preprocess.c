/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_preprocess.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 08:12:21 by alienard          #+#    #+#             */
/*   Updated: 2020/10/28 14:57:14 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_pre_exec(t_cmd *cmd, t_sh *sh)
{
	int	i;

	if (cmd->pipe_next && (ft_init_pipe(sh, cmd)))
		ft_parse_cmds(cmd->pipe_next, sh);
	ft_check_env_var(cmd, sh);
	ft_clean_envvar(cmd);
	i = -1;
	while (cmd->av[++i])
		cmd->av[i] = ft_strdup_clean(cmd->av[i]);
	if (cmd->av[0] == NULL)
		return (1);
	if (cmd->cmd)
		free(cmd->cmd);
	cmd->cmd = ft_strdup(cmd->av[0]);
	return (0);
}

int			ft_parse_cmds(t_cmd *cmd, t_sh *sh)
{
	char	**builtins;
	int		i;

	if (ft_pre_exec(cmd, sh) == 1)
		return (1);
	i = -1;
	if (ft_strcmp(cmd->cmd, "exit") == 0)
		return (ft_exit(cmd, sh));
	if (ft_strcmp(cmd->cmd, "cd") == 0)
		return (ft_change_dir(cmd, sh));
	if (ft_strcmp(cmd->cmd, "export") == 0 && cmd->av[1]
		&& ft_strlen(cmd->av[1]) > 0)
		return (ft_export(cmd, sh));
	if (ft_strcmp(cmd->cmd, "unset") == 0)
		return (ft_unset(cmd, sh));
	builtins = ft_split("echo,pwd,env,export", ',');
	while (builtins[++i])
	{
		if (ft_strcmp(cmd->cmd, builtins[i]) == 0
			&& !(ft_free_split(builtins)))
			return (ft_blt_process(sh, cmd, sh->blt_fct[i]));
	}
	ft_free_double_array(builtins);
	return (ft_process(cmd, sh));
}

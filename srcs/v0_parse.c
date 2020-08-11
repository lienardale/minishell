/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v0_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 08:12:21 by alienard          #+#    #+#             */
/*   Updated: 2020/08/11 18:40:45 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

int		ft_exec_redir_out(t_sh *sh, t_cmd *cmd)
{
	if ((cmd->fdout = open(cmd->file_redir, O_WRONLY | O_CREAT | O_TRUNC, 0777)) == -1)
	{
		ft_dprintf(2, "Error in open exec_redir_out.\n");
		return (0);
	}
	if ((cmd->ret_dup = dup2(cmd->fdout, STDOUT_FILENO)) < 0
		&& (write(1,"dup2 failed\n",ft_strlen("dup2 failed\n"))))
		return (ft_exit((t_cmd*)(sh->cmds->head), sh));
	return (1);
}

int		ft_exec_append(t_sh *sh, t_cmd *cmd)
{
	if ((cmd->fdout = open(cmd->file_redir, O_WRONLY | O_CREAT | O_APPEND, 0777)) == -1)
	{
		ft_dprintf(2, "Error in open exec_append.\n");
		return (0);
	}
	if ((cmd->ret_dup = dup2(cmd->fdout, STDOUT_FILENO)) < 0
		&& (write(1,"dup2 failed\n",ft_strlen("dup2 failed\n"))))
		return (ft_exit((t_cmd*)(sh->cmds->head), sh));
	return (1);
}

int		ft_exec_redir_in(t_sh *sh, t_cmd *cmd)
{
	if ((cmd->fdin = open(cmd->file_redir, O_RDONLY)) == -1)
	{
		// ft_dprintf(2, "Error in open exec_redir_in.\n");
		// return (1);
	}
	if ((cmd->ret_dup = dup2(cmd->fdin, STDIN_FILENO)) < 0
		/*&& (write(1,"dup2 failed\n",ft_strlen("dup2 failed\n")))*/)
		return (ft_exit((t_cmd*)(sh->cmds->head), sh));
	return (1);
}

int		ft_blt_process(t_sh *sh, t_cmd *cmd,
			int (*fn)(t_cmd *cmd, t_sh *sh))
{
	pid_t	child;
	pid_t	wpid;
	int		status;
//	int		ret;

	child = fork();
	if (child < 0)
	{
		ft_dprintf(2, "Error forking\n");
		return (0);
	}
	else if (child > 0)
	{
	printf("je suis dans le parent, sh->cmd :%d %p\n", sh->ret_cmd, sh);
		wpid = waitpid(child, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			wpid = waitpid(child, &status, WUNTRACED);
	printf("je suis dans le parent, sh->cmd :%d %p\n", sh->ret_cmd, sh);
		return (sh->ret_cmd);
	}
	else
	{
		if (cmd->redir)
			ft_exec_redir(sh, cmd);
//		ret = fn(cmd, sh);
		sh->ret_cmd = fn(cmd, sh);
//		exit(ret);
	printf("je suis dans l'enfant, sh->cmd :%d %p\n", sh->ret_cmd, sh);
		exit(sh->ret_cmd);
		return (sh->ret_cmd);
	}
	return (sh->ret_cmd);
}

int		ft_parse_cmds(t_cmd *cmd, t_sh *sh)
{
	char	**builtins;
	int		i;
	int		pipefd[2];
//	int		ret;

	ft_check_env_var(cmd, sh);
//	// cmd->av = ft_lst_to_split(cmd->argv, free);
	if (pipe(pipefd) < 0)
	{
		ft_dprintf(2, "Pipe failed to initialize\n");
		return (2);
	}
	if (cmd->cmd == NULL) // empty cmd entered
		return (1);
	i = -1;
	if (ft_strcmp(cmd->cmd, "exit") == 0)
		return (ft_exit(cmd, sh));
	if (ft_strcmp(cmd->cmd, "cd") == 0)
		return (ft_change_dir(cmd, sh));
	if (ft_strcmp(cmd->cmd, "export") == 0)
		return (ft_export(cmd, sh));
	if (ft_strcmp(cmd->cmd, "unset") == 0)
		return (ft_unset(cmd, sh));
	builtins = ft_split("exit,echo,pwd,env,cd,export,unset", ',');
	while (builtins[++i])
	{
		if (ft_strcmp(cmd->cmd, builtins[i]) == 0)
		{
			sh->ret_cmd = ft_blt_process(sh, cmd, sh->blt_fct[i]);
			ft_free_double_array(builtins);
			return (sh->ret_cmd);
		}
	}
	ft_free_double_array(builtins);
	return (ft_process(cmd, sh));
}

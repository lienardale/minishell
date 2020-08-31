/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v0_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 08:12:21 by alienard          #+#    #+#             */
/*   Updated: 2020/08/31 13:47:31 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

int		ft_exec_redir_out(t_sh *sh, t_cmd *cmd)
{
	if ((cmd->fdout = open(cmd->file_redir, O_WRONLY | O_CREAT
		| O_TRUNC, 0777)) == -1)
	{
		// ft_dprintf(2, "Error in open exec_redir_out.\n");
		return (0);
	}
	if ((cmd->ret_dup = dup2(cmd->fdout, STDOUT_FILENO)) < 0
		&& (write(1, "dup2 failed\n", ft_strlen("dup2 failed\n"))))
		return (ft_exit((t_cmd*)(sh->cmds->head), sh));
	return (1);
}

int		ft_exec_append(t_sh *sh, t_cmd *cmd)
{
	if ((cmd->fdout = open(cmd->file_redir, O_WRONLY | O_CREAT
		| O_APPEND, 0777)) == -1)
	{
		// ft_dprintf(2, "Error in open exec_append.\n");
		return (0);
	}
	if ((cmd->ret_dup = dup2(cmd->fdout, STDOUT_FILENO)) < 0
		&& (write(1, "dup2 failed\n", ft_strlen("dup2 failed\n"))))
		return (ft_exit((t_cmd*)(sh->cmds->head), sh));
	return (1);
}

int		ft_exec_redir_in(t_sh *sh, t_cmd *cmd)
{
	cmd->fdin = open(cmd->file_redir, O_RDONLY);
	if ((cmd->ret_dup = dup2(cmd->fdin, STDIN_FILENO)) < 0)
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
	if (child < 0 && ft_dprintf(2, "Error forking\n"))
		return (0);
	else if (child > 0)
	{
		if (cmd->pipe_prev || cmd->pipe_next)
			ft_exec_pipe_parent(sh, cmd);
//	printf("je suis dans le parent, sh->cmd :%d %p\n", sh->ret_cmd, sh);
		wpid = waitpid(child, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			wpid = waitpid(child, &status, WUNTRACED);
//	printf("ceci est la valeur de status :%d \n", status);
//	printf("je suis dans le parent, sh->cmd :%d %p\n", sh->ret_cmd, sh);
// la valeur de retour de la fonction est sur le 2eme octet, donc il faut tout diviser par 256
		return (status / 256);
	}
	else
	{
		if (cmd->pipe_prev || cmd->pipe_next)
			ft_exec_pipe_child(sh, cmd);
		if (cmd->redir)
			ft_exec_redir(sh, cmd);
//		ret = fn(cmd, sh);
		sh->ret_cmd = fn(cmd, sh);
//		exit(ret);
//	printf("je suis dans l'enfant, sh->cmd :%d %p\n", sh->ret_cmd, sh);
		exit(sh->ret_cmd);
		return (sh->ret_cmd);
	}
	return (sh->ret_cmd);
}

int		ft_parse_cmds(t_cmd *cmd, t_sh *sh)
{
	char	**builtins;
	int		i;
	// int		ret;

	if (cmd->pipe_next && (ft_init_pipe(sh, cmd)))
		ft_parse_cmds(cmd->pipe_next, sh);
//else if (cmd->pipe_next) //ft_init_pipe() fails
	// printf("ARGS0:|%s|\n", (char*)cmd->argv->content);
	ft_check_env_var(cmd, sh);
	ft_lstclear(&cmd->argv, free);
	// add suppression of $ that must be
	i = -1;
	while (cmd->av[++i])
		cmd->av[i] = ft_strdup_clean(cmd->av[i]);
// already in v0_split.c line 73 
//	cmd->cmd= ft_strdup(cmd->av[0]);
//	if (cmd->cmd == NULL)
//		return (1);
	i = -1;
// pour ne pas faire d'enfant (fork)
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
//printf("je suis dans ft_parse_cmds, sh->cmd :%d %p\n", sh->ret_cmd, sh);
			sh->ret_cmd = ft_blt_process(sh, cmd, sh->blt_fct[i]);
//printf("je suis dans ft_parse_cmds, sh->cmd :%d %p\n", sh->ret_cmd, sh);
			ft_free_double_array(builtins);
			return (sh->ret_cmd);
		}
	}
	ft_free_double_array(builtins);
	return (ft_process(cmd, sh));
}

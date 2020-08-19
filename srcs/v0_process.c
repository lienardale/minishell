/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v0_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 08:11:25 by alienard          #+#    #+#             */
/*   Updated: 2020/08/19 18:11:24 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

char	*ft_get_onlypaths(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}

char	*ft_findexec(char *path, char *exec)
{
	DIR				*dir;
	struct dirent	*tmp;
	char			*result;
	int				len;

	result = NULL;
	dir = opendir(path);
	if (!dir)
		return (NULL);
	while ((tmp = readdir(dir)))
	{
		if (ft_strcmp(tmp->d_name, exec) == 0)
		{
			len = ft_strlen(path) + ft_strlen(exec) + 2;
			result = ft_calloc(1, len);
			ft_strlcat(result, path, len);
			ft_strlcat(result, "/", len);
			ft_strlcat(result, exec, len);
			closedir(dir);
			return (result);
		}
	}
	closedir(dir);
	return (result);
}

char	*ft_get_abspath_filename(char *exec, char **env, t_sh *sh)
{
	char	*tmp;
	char	**paths;
	char	*result;
	int		i;

	i = 0;
	if (!(tmp = ft_get_onlypaths(env)))
	{
		if (sh->nbline)
			ft_dprintf(2, "%s: line %d: %s: No such file or directory\n", sh->file, sh->nbline, exec);
		else
			ft_dprintf(2, "minishell: %s: No such file or directory\n", exec);
		exit(EXIT_FAILURE);
	}
	else if (!(paths = ft_split(tmp, ':')))
		return (0);
	while (paths[i])
	{
		if ((result = ft_findexec(paths[i], exec)))
		{
			ft_free_split(paths);
			return (result);
		}
		i++;
	}
	ft_free_split(paths);
	return (result);
}

void	ft_search_n_execute(char **args, char **env, t_sh *sh)
{
	int		exec_start;
	char	*exec;
	char	*temp;

	exec = NULL;
	temp = args[0];
	if ((exec_start = ft_isolate_exec(args[0], &exec)) != -1)
		args[0] = ft_parse_path(args[0]);
	else
		args[0] = (ft_get_abspath_filename(args[0], env, sh));
	if (exec)
		free(exec);
	else if (!args[0])
	{
		args[0] = temp;
		if (sh->nbline)
			ft_dprintf(2, "%s: line %d: %s: command not found\n", sh->file, sh->nbline, args[0]);
		else
			ft_dprintf(2, "minishell: %s: command not found\n", args[0]);
		exit(EXIT_FAILURE);
	}
	if (execve(args[0], args, env) == -1)
	{
		free(args[0]);
		args[0] = temp;
		if (sh->nbline)
			ft_dprintf(2, "%s: line %d: %s: No such file or directory\n", sh->file, sh->nbline, args[0]);
		else
			ft_dprintf(2, "minishell: %s: No such file or directory\n", args[0]);
		exit(EXIT_FAILURE);
	}
	free(args[0]);
	args[0] = temp;
}

int			ft_process(t_cmd *cmd, t_sh *sh)
{
	pid_t	pid;
	pid_t	wpid;
	int		status;
	char	**split_env;

	split_env = NULL;
	pid = fork();
	if (pid == 0)
	{
		// Child process
		if (cmd->pipe_prev || cmd->pipe_next)
			cmd->ret_dup = ft_exec_pipe_child(sh, cmd);
		if (cmd->redir)
			ft_exec_redir(sh, cmd);
		split_env = ft_lst_env_to_split_launch(*(sh->env));
		ft_search_n_execute(cmd->av, split_env, sh);
		ft_free_split(split_env);
		if (cmd->redir)
			(close(cmd->fdout) < 0 ) ? ft_dprintf(2, "Close of fd_out not ok\n") : 0;
		// if (cmd->ret_dup)
		// {
		// 	(close(cmd->pipedfd[0]) < 0 ) ? ft_dprintf(2, "Close of pipedfd[0] not ok\n") : 0;
		// 	(close(cmd->pipedfd[1]) < 0 ) ? ft_dprintf(2, "Close of pipedfd[1] not ok\n") : 0;
		// 	exit(1);
		// 	return(1);
		// }
	}
	else if (pid < 0 && ft_dprintf(2, "Error forking\n"))
		return (0);
	else
	{
		// Parent process
		wpid = waitpid(pid, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			wpid = waitpid(pid, &status, WUNTRACED);
		if (cmd->pipe_prev || cmd->pipe_next)
			ft_exec_pipe_parent(sh, cmd);
		// return (1);
		// freeing allocated memory
		// ft_free_double_array(args);
	}
	return (1);
}

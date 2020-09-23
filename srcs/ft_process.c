/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 08:11:25 by alienard          #+#    #+#             */
/*   Updated: 2020/09/23 17:17:54 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*ft_get_onlypaths(char **env)
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

char		*ft_findexec(char *path, char *exec)
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

char		*ft_get_abspath_filename(char *exec, char **env, t_sh *sh)
{
	char	*tmp;
	char	**paths;
	char	*result;
	int		i;

	i = 0;
	if (!(tmp = ft_get_onlypaths(env)))
	{
		ft_redirerror(sh, exec, "No such file or directory");
		exit(EXIT_FAILURE);
	}
	else if (!(paths = ft_split(tmp, ':')))
		return (0);
	while (paths[i])
	{
		if ((result = ft_findexec(paths[i], exec)))
		{
			(paths) ? ft_free_split(paths) : 0;
			return (result);
		}
		i++;
	}
	(paths) ? ft_free_split(paths) : 0;
	return (result);
}

int			ft_search_n_execute(char **args, char **env, t_sh *sh)
{
	char	*exec;
	char	*temp;
	int		ret;

	exec = NULL;
	temp = args[0];
	if (ft_isolate_exec(args[0], &exec) != -1)
		temp = ft_parse_path(&args[0]);
	else
		temp = ft_get_abspath_filename(temp, env, sh);
	if (exec)
		free(exec);
	else if (!temp)
	{
		ft_redirerror(sh, args[0], "command not found");
		exit(127);
	}
	if ((ret = execve(temp, args, env)) == -1)
	{
		ft_redirerror(sh, temp, "No such file or directory");
		exit(127);
	}
	ft_safe_free((void**)&temp);
	return (ret);
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
		return (ft_process_child(cmd, sh));
	else if (pid < 0 && ft_dprintf(2, "Error forking\n"))
		return (0);
	else
	{
		wpid = waitpid(pid, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			wpid = waitpid(pid, &status, WUNTRACED);
		if (cmd->pipe_prev || cmd->pipe_next)
			ft_exec_pipe_parent(sh, cmd);
		if (WIFEXITED(status))
			return (status / 256);
		else if (WIFSIGNALED(status))
			return (status + 128);
	}
	return (1);
}

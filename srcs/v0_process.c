/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v0_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 08:11:25 by alienard          #+#    #+#             */
/*   Updated: 2020/06/30 17:10:21 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

static char	*ft_get_onlypaths(char **env)
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

static char	*ft_findexec(char *path, char *exec)
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

static char	*ft_get_abspath_filename(char *exec, char **env)
{
	char	*tmp;
	char	**paths;
	char	*result;
	int		i;

	i = 0;
	if (!(tmp = ft_get_onlypaths(env)))
		return (0);
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

static void	ft_search_n_execute(char **args, char **env)
{
	int		exec_start;
	char	*exec;
	char	*temp;

	exec = NULL;
	temp = args[0];
	if ((exec_start = ft_isolate_exec(args[0], &exec)) != -1)
		args[0] = ft_parse_path(args[0]);
	else
		args[0] = (ft_get_abspath_filename(args[0], env));
	if (exec)
		free(exec);
	else if (!args[0])
	{
		args[0] = temp;
		ft_dprintf(2, "minishell: command not found: |%s|\n", args[0]);
		exit(EXIT_FAILURE);
	}
	if (execve(args[0], args, env) == -1)
	{
		free(args[0]);
		args[0] = temp;
		ft_dprintf(2, "error execve\n");
		exit(EXIT_FAILURE);
	}
	free(args[0]);
	args[0] = temp;
}

int			ft_launch(char **args, t_list **env)
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
		split_env = ft_lst_env_to_split(*env);
		ft_search_n_execute(args, split_env);
		ft_free_split(split_env);
	}
	else if (pid < 0)
	{
		// Error forking
		ft_dprintf(2, "error forking\n");
		// freeing allocated memory
		// ft_free_double_array(args);
		return (0);
	}
	else
	{
		// Parent process
		wpid = waitpid(pid, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			wpid = waitpid(pid, &status, WUNTRACED);
		// freeing allocated memory
		// ft_free_double_array(args);
	}
	return (1);
}

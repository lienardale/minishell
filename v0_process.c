/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v0_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 08:11:25 by alienard          #+#    #+#             */
/*   Updated: 2020/05/18 08:51:14 by alienard         ###   ########.fr       */
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

char	*ft_get_abspath_filename(char *exec, char **env)
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
			return (result);
		}
		i++;
	}
	return (result);
}

int		ft_launch(char **args, char **env)
{
	pid_t	pid;
	pid_t	wpid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		// Child process
		args[0] = (ft_get_abspath_filename(args[0], env));
		if (execve(args[0], args, env) == -1)
		{
			// freeing allocated memory
			ft_free_double_array(args);
			// perror("error execve");
			ft_dprintf(2, "error execve\n");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
	{
		// Error forking
		ft_dprintf(2, "error forking\n");
		// perror("error forking");
		// freeing allocated memory
		ft_free_double_array(args);
		return (0);
	}
	else
	{
		// Parent process
		wpid = waitpid(pid, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			wpid = waitpid(pid, &status, WUNTRACED);
	}
	// freeing allocated memory
	ft_free_double_array(args);
	return (1);
}

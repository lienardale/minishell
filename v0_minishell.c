/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v0_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 13:06:27 by alienard          #+#    #+#             */
/*   Updated: 2020/04/29 19:05:22 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

char *ft_get_onlypaths(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
			return (ft_strtrim(env[i], "PATH="));
		i++;
	}
	return (NULL);
}

char *ft_findexec(char *path, char *exec)
{
	DIR *dir;
	struct dirent *tmp;
	char *result;
	int len;

	result = 0;
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
			return result;
		}
	}
	closedir(dir);
	return result;
}

char *ft_get_abspath_filename(char *exec, char **env)
{
	char *tmp;
	char **paths;
	char *result;
	int i;

	i = 0;
	tmp = ft_get_onlypaths(env);
	paths = ft_split(tmp, ':');
	while (paths[i])
	{
		if ((result = ft_findexec(paths[i], exec)))
			return (result);
		i++;
	}
	return (result);
}

int ft_launch(char **args, char **env)
{
	pid_t	pid;
	pid_t	wpid;
	int		status;
	// char	*tmp;
	// char	**envp;

	pid = fork();
	if (pid == 0)
	{
		// Child process
		// if (execvp(args[0], args) == -1)
		// tmp = ft_strtrim(env[1], "PATH=");
		// envp = ft_split(tmp, ':');
		args[0] = (ft_get_abspath_filename(args[0], env));
		if (execve(args[0], args, env) == -1)
		{
			ft_dprintf(2, "error execve\n");
			// perror("error execve");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
	{
		// Error forking
		perror("error forking");
		return (0);
	}
	else
	{
		// Parent process
		wpid = waitpid(pid, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			wpid = waitpid(pid, &status, WUNTRACED);
	}
	return 1;
}

int		ft_parse_line(char **args, char **env)
{
	if (args[0] == NULL)
	{
	// An empty command was entered.
		return (1);
	}
	if (ft_strcmp(args[0], "exit") == 0)
		return (0);
	return ft_launch(args, env);
}

char	**ft_split_line(char *line)
{
	int pos;
	char **tokens;

	pos = -1;
	tokens = ft_split_charset(line, SPACE);
	if (!tokens)
	{
		ft_dprintf(2, "minishell: allocation error\n");
		exit(EXIT_FAILURE);
	}
	return (tokens);
}

void	ft_prompt(int *check, int fd, char **env)
{
	char	*line;
	char	**args;
	int		ret;
	int		i;

	ret = 1;
	while (ret && (write(1,">",1)) && (*check = get_next_line(fd, &line)) >= 0)
	{
		i = 0;
		args = ft_split_line(line);
		ft_free_ptr(line);
		ret = ft_parse_line(args, env);
		while (args[i])
			ft_free_ptr(args[i++]);
		ft_free_ptr(args);
		if (*check == 0)
			break ;
	}
}

int	main(int ac, char **av, char **env)
{
	int		check;
	int		i;
	// t_sh	sh;

	if (ac != 1)
		return EXIT_FAILURE;
	(void)av;
	for (i = 0; env[i] != NULL; i++)
		ft_printf("%s\n", env[i]);
	ft_prompt(&check, 0, env);
	system("leaks minishell");
	return (check == 0) ? EXIT_FAILURE : EXIT_SUCCESS;
}

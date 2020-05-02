/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v0_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 08:11:25 by alienard          #+#    #+#             */
/*   Updated: 2020/05/02 08:16:05 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

int		ft_launch(char **args, char **env)
{
	pid_t	pid;
	pid_t	wpid;
	int		status;
	int		i;
	// char	*tmp;
	// char	**envp;

	pid = fork();
	if (pid == 0)
	{
		// Child process
		// if (execvp(args[0], args) == -1)
		// tmp = ft_strtrim(env[1], "PATH=");
		// envp = ft_split(tmp, ':');
		args[0] = "/bin/ls";
		for (i = 0; args[i] != NULL; i++)
			ft_printf("%s\n", args[i]);
		if (execve(args[0], args, env) == -1)
		{
			// ft_dprintf(2, "error execve\n");
			perror("error execve");
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

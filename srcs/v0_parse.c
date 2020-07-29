/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v0_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 08:12:21 by alienard          #+#    #+#             */
/*   Updated: 2020/07/29 11:30:57 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

int		ft_exec_redir_out(t_sh *sh, t_cmd *cmd)
{
	if ((cmd->fdout = open(cmd->redir, O_WRONLY | O_CREAT | O_TRUNC, 0777)) == -1)
	{
		ft_dprintf(2, "Error in open.\n");
		return (0);
	}
	if ((cmd->ret_dup = dup2(cmd->fdout, STDOUT_FILENO)) < 0 && (write(1,"dup2 failed\n",ft_strlen("dup2 failed\n"))))
		return (ft_exit((t_cmd*)(sh->cmds->head), sh));
	return (1);
}

int		ft_blt_process(t_sh *sh, t_cmd *cmd,
			int (*fn)(t_cmd *cmd, t_sh *sh))
{
	pid_t	child;
	pid_t	wpid;
	int		status;
	int		ret;

	child = fork();
	if (child < 0)
	{
		ft_dprintf(2, "Error forking\n");
		return (0);
	}
	if (child > 0)
	{
		wpid = waitpid(child, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			wpid = waitpid(child, &status, WUNTRACED);
		return (1);
	}
	else
	{
		if (cmd->redir)
			ft_exec_redir_out(sh, cmd);
		ret = fn(cmd, sh);
		exit(ret);
		return (ret);
	}
	return (1);
}

char	*ft_strdup_env_var(int len, char *av, char *key)
{
	char	*tab;
	int		i;
	int		j;
	int 	k;
	int		l;

	j = -1;
	k = 1;
	i = 0;
	l = 0;
	if (!(tab = ft_calloc(len, sizeof(char))))
		return (NULL);
	while (av[++j] && (av[j] != '$' || ft_isinquotes(av, j) || ft_is_escaped(av, j)))
		tab[j] = av[j];
	i = j;
	while (av[j + k] && (av[j + k] != '$' || ft_is_escaped(av, j + k) || ft_isinquotes(av, j + k))
		&& (!ft_isspace(av[j + k]) || ft_is_escaped(av, j + k) || ft_isinquotes(av, j + k)))
		k++;
	while (key[l])
		tab[i++] = key[l++];
	while (av[j + k])
	{
		tab[i] = av[j + k];
		i++;
		j++;
	}
	free(av);
	return (tab);
}

void	ft_replace_env_var(char *av, char *key, t_cmd *cmd, int	i)
{
	int		j;
	int 	k;
	int		len;

	j = 0;
	k = 0;
	len = 0;
	while (av[j] && (av[j] != '$' || ft_isinquotes(av, j) || ft_is_escaped(av, j)))
		j++;
	len = ft_strlen(key);
	k = (av[j] == '$') ? k + 1 : k;
	while (av[j + k] && (av[j + k] != '$' || ft_is_escaped(av, j + k) || ft_isinquotes(av, j + k))
		&& (!ft_isspace(av[j + k]) || ft_is_escaped(av, j + k) || ft_isinquotes(av, j + k)))
		k++;
	while (av[j + k])
		j++;
	len += j;
	cmd->av[i] = ft_strdup_env_var(len, av, key);
}

char		*ft_is_in_env(char *str, t_sh *sh)
{
	char	*tmp;
	int		i;
	t_list	*env;

	i = 1;
	env = *(sh->env);
	while (str[i] && (str[i] != '$' || ft_is_escaped(str, i) || ft_isinquotes(str, i))
		&& (!ft_isspace(str[i]) || ft_is_escaped(str, i) || ft_isinquotes(str, i)))
		i++;
	tmp = ft_substr(str, 1, i - 1);
	while (env)
	{
		if(ft_strncmp(((t_env*)(env->content))->key, tmp, ft_strlen(tmp)) == 0)
			return (((t_env*)(env->content))->value);
		env = env->next;
	}
	return (NULL);
}

void	ft_check_env_var(t_cmd *cmd, t_sh *sh)
{
	char	*key_val;
	char	**av;
	int		i;
	int		j;

	av = cmd->av;
	i = 0;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] == '$' && !ft_isinquotes(av[i], j) && !ft_is_escaped(av[i], j))
			{
				key_val = NULL;
				key_val = ft_is_in_env(&av[i][j], sh);
				if (key_val)
				{
					ft_replace_env_var(cmd->av[i], key_val, cmd, i);
					j = 0;
				}
			}
			j++;
		}
		i++;
	}

}

int		ft_parse_cmds(t_cmd *cmd, t_sh *sh)
{
	char	**builtins;
	int		i;
	int		pipefd[2];
	int		ret;

	ft_check_env_var(cmd, sh);
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
			ret = ft_blt_process(sh, cmd, sh->blt_fct[i]);
			ft_free_double_array(builtins);
			return (ret);
		}
	}
	ft_free_double_array(builtins);
	return (ft_launch(cmd, sh));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 14:40:49 by alienard          #+#    #+#             */
/*   Updated: 2020/10/28 17:30:29 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_is_double_minus(char *str)
{
	int	i;

	i = 0;
	while (str[i] == '-')
		i++;
	if (i == 2 && str[i] == 0)
		return (1);
	return (0);
}

int			ft_search_piped_exit_cmd(t_sh *sh)
{
	t_dlist	*cmd;
	t_cmd	*pipe;

	if (!sh->cmds)
		return (1);
	cmd = (t_dlist *)(sh->cmds->head);
	while (cmd)
	{
		pipe = (t_cmd*)(cmd->data);
		if (ft_strcmp(pipe->cmd, "exit") == 0 && !(pipe->pipe_next))
			return (1);
		while (pipe)
		{
			if (ft_strcmp(pipe->cmd, "exit") == 0)
				return (0);
			pipe = pipe->pipe_next;
		}
		cmd = cmd->next;
	}
	return (1);
}

void		ft_exit_toomanyargs(t_sh *sh, t_cmd *cmd, int ret)
{
	(void)ret;
	if (!sh->file && ret)
		ft_isatty(0) ? ft_dprintf(2, "exit\n") : 0;
	if (ft_isdigit(cmd->av[1][0]))
		sh->nbline ? ft_dprintf(2,
			"%s: line %d: exit: too many arguments\n",
			sh->file, sh->nbline)
			: ft_dprintf(2,
			"minishell: exit: too many arguments\n");
	else
	{
		ft_strerror(cmd, sh, "numeric argument required");
		ret ? ft_free_minishell(sh, 2) : 0;
	}
}

void		ft_exit_twoargs(t_sh *sh, t_cmd *cmd, int ret)
{
	int		return_value;

	if (ft_is_double_minus(cmd->av[1]))
		ret ? ft_free_minishell(sh, sh->ret_cmd) : 0;
	if (ft_str_isdigit(cmd->av[1])
		&& ft_is_in_min_max_atoi_long(cmd->av[1]))
	{
		return_value = ft_atoi_long(cmd->av[1]) % 256;
		return_value = (return_value < 0) ? return_value + 256
			: return_value;
		ret ? ft_free_minishell(sh, return_value) : 0;
	}
	else
	{
		if (!sh->file && ret)
			ft_isatty(0) ? ft_dprintf(2, "exit\n") : 0;
		ft_strerror(cmd, sh, "numeric argument required");
		ret ? ft_free_minishell(sh, 2) : 0;
	}
}

int			ft_exit(t_cmd *cmd, t_sh *sh)
{
	int		i;
	int		ret;

	i = 0;
	ret = ft_search_piped_exit_cmd(sh);
	if (!cmd && !sh->file)
	{
		ft_isatty(0) ? ft_dprintf(2, "exit\n") : 0;
		ret ? ft_free_minishell(sh, sh->ret_cmd) : 0;
	}
	if (!cmd && sh->file)
		ret ? ft_free_minishell(sh, sh->ret_cmd) : 0;
	while (cmd->av[i])
		i++;
	if (i > 2)
		ft_exit_toomanyargs(sh, cmd, ret);
	else if (i == 2)
		ft_exit_twoargs(sh, cmd, ret);
	else if (ret)
	{
		if (!sh->file && ret)
			ft_isatty(0) ? ft_dprintf(2, "exit\n") : 0;
		ft_free_minishell(sh, sh->ret_cmd);
	}
	return (0);
}

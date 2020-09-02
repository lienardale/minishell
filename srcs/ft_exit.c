/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 14:40:49 by alienard          #+#    #+#             */
/*   Updated: 2020/09/02 17:41:17 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_double_minus(char *str)
{
	int	i;

	i = 0;
	while (str[i] == '-')
		i++;
	if (i == 2 && str[i] == 0)
		return (1);
	return (0);
}

void		ft_free_sub_cmd(t_cmd *cmd)
{
	if (cmd->pipe_next)
		ft_free_sub_cmd(cmd->pipe_next);
	if (cmd->env)
		ft_lstclear(cmd->env, ft_free_env_lst);
	if (cmd->argv)
		ft_lstclear(&cmd->argv, free);
	if (cmd->av)
		ft_free_double_array(cmd->av);
	if (cmd)
		ft_free_ptr(cmd->av);
	if (cmd->file_redir)
		ft_free_ptr(cmd->file_redir);
	if (cmd->fd_in)
		ft_lstclear(cmd->fd_in, free);
	if (cmd->fd_out)
		ft_lstclear(cmd->fd_out, free);
	if (cmd)
		free(cmd);
}

void		ft_free_cmd(t_dlist *node)
{
	t_cmd	*cmd;

	cmd = (t_cmd*)node->data;
	if (cmd->env)
		ft_lstclear(cmd->env, ft_free_env_lst);
	if (cmd->argv)
		ft_lstclear(&cmd->argv, free);
	if (cmd->av)
		ft_free_double_array(cmd->av);
	if (cmd)
		ft_free_ptr(cmd->av);
	if (cmd->file_redir)
		ft_free_ptr(cmd->file_redir);
	if (cmd->fd_in)
		ft_lstclear(cmd->fd_in, free);
	if (cmd->fd_out)
		ft_lstclear(cmd->fd_out, free);
	if (cmd->pipe_next)
		ft_free_sub_cmd(cmd->pipe_next);
	if (node)
		free(node);
}

void		ft_free_minishell(t_sh *sh)
{
	t_dlist	*tmp;
	t_dlist	*tmp2;

	if (sh->line)
		free(sh->line);
	if (sh->env)
		ft_lstclear(sh->env, ft_free_env_lst);
	if (sh->cmds)
	{
		tmp = sh->cmds->head;
		tmp2 = sh->cmds->head;
		while (tmp)
		{
			tmp2 = tmp2->next;
			ft_free_cmd(tmp);
			tmp = tmp2;
		}
	}
}

int			ft_exit(t_cmd *cmd, t_sh *sh)
{
	int		i;
	int		return_value;

	i = 0;
	if (!cmd && !sh->file)
	{
		return_value = sh->ret_cmd;
		ft_lstclear(sh->env, ft_free_env_lst);
		ft_free_minishell(sh);
		ft_dprintf(2, "exit\n");
		exit(return_value);
	}
	if (!cmd && sh->file)
	{
		return_value = sh->ret_cmd;
		ft_lstclear(sh->env, ft_free_env_lst);
		ft_free_minishell(sh);
		exit(return_value);
	}
	while (cmd->av[i])
		i++;
	if (i > 2)
	{
		ft_dprintf(2, "minishell: exit: too many arguments\n");
		// ft_free_minishell(sh);
		exit(1);
	}
	else if (i == 2)
	{
		if (ft_is_double_minus(cmd->av[1]))
		{
			return_value = sh->ret_cmd;
			// ft_free_minishell(sh);
			exit(return_value);
		}
		if (ft_str_isdigit(cmd->av[1]) && ft_is_in_min_max_atoi_long(cmd->av[1]))
		{
// over int max
//			ft_free_sh();
			return_value = ft_atoi_long(cmd->av[1]) % 256;
			return_value = (return_value < 0) ? return_value + 256 : return_value;
			// ft_free_minishell(sh);
			exit(return_value);
		}
		else
		{
			ft_dprintf(2, "minishell: exit: %s: numeric argument required\n", cmd->av[1]);
			// ft_free_minishell(sh);
			exit(255);
		}
	}
	else
	{
		return_value = sh->ret_cmd;
		// ft_free_minishell(sh);
		exit(return_value);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard@student.42.fr <alienard>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 14:40:49 by alienard          #+#    #+#             */
/*   Updated: 2020/09/10 18:51:44 by alienard@st      ###   ########.fr       */
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
	if (cmd->cmd)
		ft_free_ptr(cmd->cmd);
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
	if (cmd->cmd)
		ft_free_ptr(cmd->cmd);
	if (cmd->file_redir)
		ft_free_ptr(cmd->file_redir);
	if (cmd->fd_in)
		ft_lstclear(cmd->fd_in, free);
	if (cmd->fd_out)
		ft_lstclear(cmd->fd_out, free);
	if (cmd->pipe_next)
		ft_free_sub_cmd(cmd->pipe_next);
	if (cmd)
		free(cmd);
	if (node)
		free(node);
}

void		ft_lstclear_env(t_list **env)
{
	t_list	*cur;
	t_list	*tmp;

	cur = *env;
	while (cur)
	{
		tmp = cur->next;
		ft_free_env_lst(cur->content);
		free(cur);
		cur = tmp;
	}
	free (env);
}

void		ft_free_minishell(t_sh *sh)
{
	t_dlist	*tmp;
	t_dlist	*tmp2;

	// if (sh->env)
	// 	ft_lstclear_env(sh->env);
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
		free(sh->cmds);
	}
}

int			ft_search_piped_exit_cmd(t_sh *sh)
{
	t_dlist	*cmd;
	t_cmd	*pipe;

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

int			ft_exit(t_cmd *cmd, t_sh *sh)
{
	int		i;
	int		return_value;
	int		ret;

	i = 0;
	ret = ft_search_piped_exit_cmd(sh);
	if (!cmd && !sh->file)
	{
		return_value = sh->ret_cmd;
		// ft_lstclear(sh->env, ft_free_env_lst);
		ft_dprintf(2, "exit\n");
		if (ret)
		{
			ft_free_minishell(sh);
			exit(return_value);
		}
	}
	if (!cmd && sh->file)
	{
		return_value = sh->ret_cmd;
		// ft_lstclear(sh->env, ft_free_env_lst);
		if (ret)
		{
			ft_free_minishell(sh);
			exit(return_value);
		}
	}
	while (cmd->av[i])
		i++;
	if (i > 2)
	{
		sh->nbline ? ft_dprintf(2,
			"%s: line %d: exit: too many arguments\n",
			sh->file, sh->nbline)
			: ft_dprintf(2,
			"minishell: exit: too many arguments\n");
		if (ret)
		{
			ft_free_minishell(sh);
			exit(1);
		}
	}
	else if (i == 2)
	{
		if (ft_is_double_minus(cmd->av[1]))
		{
			return_value = sh->ret_cmd;
			if (ret)
			{
				ft_free_minishell(sh);
				exit(return_value);
			}
		}
		if (ft_str_isdigit(cmd->av[1]) && ft_is_in_min_max_atoi_long(cmd->av[1]))
		{
// over int max
//			ft_free_sh();
			return_value = ft_atoi_long(cmd->av[1]) % 256;
			return_value = (return_value < 0) ? return_value + 256 : return_value;
			if (ret)
			{
				ft_free_minishell(sh);
				exit(return_value);
			}
		}
		else
		{
			sh->nbline ? ft_dprintf(2,
			"%s: line %d: exit: %s: numeric argument required\n",
			sh->file, sh->nbline, cmd->av[1])
			: ft_dprintf(2,
			"minishell: exit: %s: numeric argument required\n", cmd->av[1]);
			if (ret)
			{
				ft_free_minishell(sh);
				exit(255);
			}
		}
	}
	else
	{
		return_value = sh->ret_cmd;
		if (ret)
		{
			ft_free_minishell(sh);
			exit(return_value);
		}
	}
	return (0);
}

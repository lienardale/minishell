/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_minishell.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 14:58:01 by alienard          #+#    #+#             */
/*   Updated: 2020/09/21 11:38:24 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_lstclear_env(t_list **env)
{
	t_list	*cur;
	t_list	*tmp;

	if (!env || !(*env))
		return ;
	cur = *env;
	while (cur)
	{
		tmp = cur->next;
		ft_free_env_lst(cur->content);
		free(cur);
		cur = tmp;
	}
}

void		ft_free_gnl(t_sh *sh)
{
	int	ret;

	while ((ret = get_next_line_multi(sh->fd, &sh->line)) >= 0)
	{
		ft_safe_free((void**)&sh->line);
		if (ret <= 0)
			break ;
	}
}

void		ft_free_minishell(t_sh *sh, int ret)
{
	if (sh->line)
		free(sh->line);
	if (sh->fd != STDIN_FILENO)
		ft_free_gnl(sh);
	if (sh->begin_input)
		ft_lstclear(&sh->begin_input, &free);
	if (sh->env)
		ft_lstclear_env(sh->env);
	if (sh->cmds)
		ft_lstclear_cmds(sh->cmds);
	if (sh->cmds)
		ft_dlst_del(sh->cmds);
	if (sh->cmds)
		free(sh->cmds);
	exit(ret);
}

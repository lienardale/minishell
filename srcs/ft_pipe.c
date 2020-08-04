/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 12:50:03 by alienard          #+#    #+#             */
/*   Updated: 2020/07/30 12:50:03 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

int		ft_add_pipe(t_dlist *cur, t_dlist *next, t_sh *sh)
{
	((t_cmd *)(cur->data))->piped_out = ((t_cmd *)(next->data));
	((t_cmd *)(next->data))->piped_in = ((t_cmd *)(cur->data));

	
	return (0);
}

int		ft_create_pipe(t_sh *sh)
{
	// t_cmd	*cmd;
	t_dlist	*cur;

	// cmd = ((t_cmd *)(sh->cmds->head));
	cur = sh->cmds->head->next;
	while (cur)
	{
		if (((t_cmd *)(cur->data))->after == '|')
			ft_add_pipe(cur, cur->next, sh);
		cur = cur->next;
	}
	return (0);
}

int		ft_init_pipe(t_sh *sh, t_cmd *cmd)
{

	return (0);
}
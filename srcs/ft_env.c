/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 17:31:08 by cdai              #+#    #+#             */
/*   Updated: 2020/09/16 17:56:22 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_cmd *cmd, t_sh *sh)
{
	t_list	*temp;
	t_env	*content;

	temp = *(sh->env);
	if (cmd->av[1])
	{
		ft_dprintf(2, "env: '%s': No such file or directory\n", cmd->av[1]);
		return (1);
	}
	while (temp)
	{
		content = (t_env*)temp->content;
		if (content->value)
		{
			ft_putstr_fd(content->key, 1);
			ft_putstr_fd("=", 1);
			ft_putendl_fd(content->value, 1);
		}
		temp = temp->next;
	}
	return (0);
}

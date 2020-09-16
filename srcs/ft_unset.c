/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 09:51:54 by cdai              #+#    #+#             */
/*   Updated: 2020/09/16 18:07:48 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_unset_check_arg(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (i == 0 && !ft_isalpha(arg[i]))
			return (1);
		else if (!ft_isalnum(arg[i]) && !ft_is_escaped(arg, i)
			&& !ft_isinquotes(arg, i))
			return (1);
		i++;
	}
	return (0);
}

int			ft_unset(t_cmd *cmd, t_sh *sh)
{
	int		i;
	int		ret;
	t_list	*to_erase;

	ret = 0;
	i = 1;
	while (cmd->av[i])
	{
		if (ft_unset_check_arg(cmd->av[i]))
		{
			ret = 1;
			ft_dprintf(2, "minishell: unset: `%s': not a valid identifier\n",
				cmd->av[i]);
		}
		else
		{
			to_erase = ft_search_env(*(sh->env), cmd->av[i]);
			if (to_erase)
				ft_lstdel_between(sh->env, to_erase->content, ft_free_env_lst);
		}
		i++;
	}
	return (ret);
}

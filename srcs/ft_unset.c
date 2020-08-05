/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 09:51:54 by cdai              #+#    #+#             */
/*   Updated: 2020/07/30 10:01:37 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

static int	ft_unset_check_arg(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (i == 0 && !ft_isalpha(arg[i]))
			return (1);
		else if (!ft_isalnum(arg[i]) && !ft_is_escaped(arg, i) && !ft_isinquotes(arg, i))
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
// return value should be 1 invalid / 0 valid
		if (ft_unset_check_arg(cmd->av[i]))
		{
			ret = 1;
			ft_printf("minishell: unset: `%s': not a valid identifier\n",
				cmd->av[i]);
		}
		else
		{
// ToDo check_valid_char (isalnum)
			to_erase = ft_search_env(*(sh->env), cmd->av[i]);
// probleme de env, ce n'est pas l'adresse qui contient env donc il faut t_list **env.
			if (to_erase)
				ft_lstdel_between(sh->env, to_erase->content, ft_free_env_lst);
			else
				ret = 1;
// en cas d'erreur de malloc, je passe.
		}
		i++;
	}
	ft_free_split(cmd->av);
// return (ret);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 07:54:41 by cdai              #+#    #+#             */
/*   Updated: 2020/09/16 17:59:41 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_export_check_underscore(char *str)
{
	if (!ft_strncmp(str, "_=", 2) || !ft_strncmp(str, "_", 2))
		return (1);
	return (0);
}

static int	ft_export_check_arg(char *arg)
{
	int	i;

	i = 0;
	if (ft_export_check_underscore(arg))
		return (0);
	while (arg[i])
	{
		if (i == 0 && !ft_isalpha(arg[i]) && arg[i] != '_')
			return (1);
		else if (arg[i] == '+' && arg[i + 1] && arg[i + 1] != '=')
			return (1);
		else if (arg[i] == '=')
			return (0);
		i++;
	}
	return (0);
}

static t_list	*ft_export_update_env(t_list *env, char *arg)
{
	t_env	*result;
	t_list	*tmp;
	bool	add;

	add = false;
	result = NULL;
	if (ft_export_check_underscore(arg))
		return (env);
	result = ft_separate_key_value(arg, &add);
	tmp = ft_update_env(env, result, add);
	return (tmp);
}

int				ft_export(t_cmd *cmd, t_sh *sh)
{
	int		i;
	char	**splited;
	int		ret;

	ret = 0;
	if (!cmd->av[1])
	{
		i = -1;
		if (!(splited = ft_lst_env_to_split_export(*(sh->env))))
			return (1);
		ft_strs_sort(splited, ft_lstsize(*(sh->env)));
		while (splited[++i])
			if (ft_strncmp(splited[i], "_=", 2))
				ft_dprintf(1, "declare -x %s\n", splited[i]);
		ft_free_split(splited);
	}
	else
	{
		i = 0;
		while (cmd->av[++i])
		{
			if (ft_export_check_arg(cmd->av[i]))
			{
				ret = 1;
				if (sh->nbline)
					ft_dprintf(2,
					"%s: line %d: export: `%s': not a valid identifier\n",
					sh->file, sh->nbline, cmd->av[i]);
				else
					ft_dprintf(2,
					"minishell: export: `%s': not a valid identifier\n",
					cmd->av[i]);
			}
			else
			{
				if (!(ft_export_update_env(*(sh->env), cmd->av[i])))
					return (1);
			}
		}
	}
	return (ret);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 07:54:41 by cdai              #+#    #+#             */
/*   Updated: 2020/09/15 17:30:57 by alienard         ###   ########.fr       */
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
// le premier character ne peut pas etre '=' ni un autre chose qu'une lettre
		if (i == 0 && !ft_isalpha(arg[i]) && arg[i] != '_')
			return (1);
		else if (arg[i] == '+' && arg[i + 1] && arg[i + 1] != '=')
			return (1);
// si je trouve un character '=' apres le premier charactere, je sors de la fonction => valide
		else if (arg[i] == '=')
			return (0);
// si je trouve un charactere autre que alpha num, je sors
		// else if (!ft_isalnum(arg[i]) && !ft_is_escaped(arg, i) && !ft_isinquotes(arg, i))
		// 	return (1);
		i++;
	}
// je retroune 0 si je valide cet argument
	return (0);
}

// les erreurs ne sont pas encore geres
static t_list	*ft_export_update_env(t_list *env, char *arg)
{
	t_env	*result;
	t_list	*tmp;
	bool	add;

	add = false;
	result = NULL;
	if (ft_export_check_underscore(arg))
	{
		// free(arg);
		return (env);
	}
	result = ft_separate_key_value(arg, &add);
	tmp = ft_update_env(env, result, add);
	// if (result)
	// 	ft_free_env_lst(result);
	// free(arg);
	return (tmp);
}

int				ft_export(t_cmd *cmd, t_sh *sh)
{
	int		i;
	char	**splited;
	int		ret;

	ret = 0;
	// ft_print_double_array(cmd->av, "av");
// je cherche a savoir si des arguments ou pas
	if (!cmd->av[1])
	{
		i = -1;
// j'utilise une variable temporaire pour ne pas modifier des choses dans la liste chainee.
// handle malloc error
		if (!(splited = ft_lst_env_to_split_export(*(sh->env))))
		{
			// ft_free_split(cmd->av);
			return (1);
		}
		ft_strs_sort(splited, ft_lstsize(*(sh->env)));
		while (splited[++i])
// il faut que je fasse attention a la variable d'env "_"
			if (ft_strncmp(splited[i], "_=", 2))
				ft_dprintf(1, "declare -x %s\n", splited[i]);
		ft_free_split(splited);
	}
// sinon je mets a jour ma variable d'environnement
	else
	{
		i = 0;
		while (cmd->av[++i])
		{
// ici la fonction est un peu differente que pour unset alors elle est specifique
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
// handle malloc error
//				
				if (!(ft_export_update_env(*(sh->env), cmd->av[i])))
				{
					// ft_free_split(cmd->av);
					return (1);
				}
			}
		}
	}
	return (ret);
}

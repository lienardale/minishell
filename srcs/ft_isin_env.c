/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 14:00:05 by alienard          #+#    #+#             */
/*   Updated: 2020/09/17 14:27:33 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_searchif_isinenv(t_list *env, char **tmp, t_sh *sh)
{
	while (env)
	{
		if (!ft_strncmp("?", (*tmp), 1))
		{
			ft_safe_free((void**)&(*tmp));
			sh->ret_str = ft_itoa(sh->ret_cmd);
			return (sh->ret_str);
		}
		else if (ft_strcmp(((t_env*)(env->content))->key,
			*tmp) == 0)
		{
			ft_safe_free((void**)&(*tmp));
			return (((t_env*)(env->content))->value);
		}
		env = env->next;
	}
	return (NULL);
}

char		*ft_is_in_env(char *str, t_sh *sh)
{
	char	*tmp;
	int		i;
	t_list	*env;
	char	*tab;

	i = 1;
	env = *(sh->env);
	while (str[i] && (str[i] != '$' || ft_is_escaped(str, i)
		|| ft_isinsquotes(str, i)) && (ft_isalnum(str[i])))
		i++;
	i = str[i] == '?' ? i + 1 : i;
	tmp = ft_substr(str, 1, i - 1);
	if (!tmp || ft_strlen(tmp) == 0)
	{
		ft_safe_free((void**)&tmp);
		return (NULL);
	}
	if ((tab = ft_searchif_isinenv(env, &tmp, sh)) != NULL)
		return (tab);
	ft_safe_free((void**)&tmp);
	return (NULL);
}

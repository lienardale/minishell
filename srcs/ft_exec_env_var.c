/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_env_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 12:14:46 by alienard          #+#    #+#             */
/*   Updated: 2020/09/16 13:09:41 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*ft_strdup_env_var(int len, char *av, char *key)
{
	char	*tab;
	int		i[4];

	i[0] = -1;
	i[1] = 0;
	i[2] = 1;
	i[3] = 0;
	if (!(tab = ft_calloc(len, sizeof(char))))
		return (NULL);
	while (av[++i[0]] && (av[i[0]] != '$' || ft_isinsquotes(av, i[0])
		|| ft_is_escaped(av, i[0])))
		tab[i[0]] = av[i[0]];
	i[1] = i[0];
	while (av[i[0] + i[2]] && (av[i[0] + i[2]] != '$'
		|| ft_is_escaped(av, i[0] + i[2]) || ft_isinsquotes(av, i[0] + i[2]))
		&& (ft_isalnum(av[i[0] + i[2]])))
		i[2]++;
	i[2] = av[i[0] + i[2]] == '?' ? i[2] + 1 : i[2];
	while (key && key[i[3]])
		tab[i[1]++] = key[i[3]++];
	while (av[i[0] + i[2]] && (i[0] + i[2]) < len)
		tab[i[1]++] = av[i[0]++ + i[2]];
	tab[i[1]] = '\0';
	free(av);
	return (tab);
}

void		ft_replace_env_var_lst(t_list *lst, char *key, t_cmd *cmd)
{
	int		i[3];
	char	*temp;
	char	**temp_strs;
	t_list	*temp_lst;
	t_list	*next;

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	temp = (char*)lst->content;
	while (temp[i[0]] && (temp[i[0]] != '$' || ft_isinsquotes(temp, i[0])
		|| ft_is_escaped(temp, i[0])))
		i[0]++;
	if (key)
		i[2] = ft_strlen(key);
	i[1] = (temp[i[0]] == '$') ? i[1] + 1 : i[1];
	while (temp[i[0] + i[1]] && (temp[i[0] + i[1]] != '$'
		|| ft_is_escaped(temp, i[0] + i[1])
		|| ft_isinsquotes(temp, i[0] + i[1]))
		&& (!ft_isalnum(temp[i[0] + i[1]])))
		i[1]++;
	while (temp[i[0] + i[1]])
		i[0]++;
	i[2] += i[0];
	// cut here
	lst->content = ft_strdup_env_var(i[2], temp, key);
	temp = lst->content;
	temp_strs = ft_split_quote(temp, ' ');
	temp_lst = ft_split_to_lst(temp_strs);
	ft_free_double_array(temp_strs);
	while (temp_lst)
	{
		next = temp_lst->next;
		ft_lstadd_before(&cmd->argv, temp_lst, lst);
		temp_lst = next;
	}
	ft_lstdel_between(&cmd->argv, lst->content, free);
}

char		*ft_is_in_env(char *str, t_sh *sh)
{
	char	*tmp;
	int		i;
	t_list	*env;

	i = 1;
	env = *(sh->env);
	while (str[i] && (str[i] != '$' || ft_is_escaped(str, i)
		|| ft_isinsquotes(str, i)) && (ft_isalnum(str[i])))
		i++;
	i = str[i] == '?' ? i + 1 : i;
	tmp = ft_substr(str, 1, i - 1);
	if (!tmp || ft_strlen(tmp) == 0)
	{
		if (tmp)
			free(tmp);
		return (NULL);
	}
	while (env)
	{
		if (!ft_strncmp("?", tmp, 1))
		{
			free(tmp);
			sh->ret_str = ft_itoa(sh->ret_cmd);
			return (sh->ret_str);
		}
		else if (ft_strcmp(((t_env*)(env->content))->key,
			tmp) == 0)
		{
			free(tmp);
			return (((t_env*)(env->content))->value);
		}
		env = env->next;
	}
	free(tmp);
	return (NULL);
}

void		ft_check_env_var(t_cmd *cmd, t_sh *sh)
{
	char	*key_val;
	int		j;
	t_list	*temp;
	char	*temp_char;

	temp = cmd->argv;
	while (temp)
	{
		j = 0;
		temp_char = (char*)temp->content;
		while (temp_char[j])
		{
			if (temp_char[j] == '$' && !ft_isinsquotes(temp_char, j)
				&& !ft_is_escaped(temp_char, j))
			{
				key_val = NULL;
				key_val = ft_is_in_env(temp_char + j, sh);
				if (key_val)
				{
					// cut btw here
					ft_replace_env_var_lst(temp, key_val, cmd);
					temp = cmd->argv;
					temp_char = (char*)temp->content;
					j = -1;
					// and here
				}
				if (sh->ret_str)
				{
					free(sh->ret_str);
					sh->ret_str = NULL;
				}
			}
			j++;
		}
		temp = temp->next;
	}
}

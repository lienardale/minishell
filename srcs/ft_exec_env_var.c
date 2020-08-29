/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_env_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 12:14:46 by alienard          #+#    #+#             */
/*   Updated: 2020/08/29 18:49:42 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

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
		&& ft_isalnum(av[i[0] + i[2]]))
		i[2]++;
	while (key[i[3]])
		tab[i[1]++] = key[i[3]++];
	while (av[i[0] + i[2]] && (i[0] + i[2]) < len)
		tab[i[1]++] = av[i[0]++ + i[2]];
	tab[i[1]] = '\0';
	free(av);
	return (tab);
}


void		ft_replace_env_var_lst(t_list *lst, char *key, t_cmd *cmd)
{
	int		j;
	int		k;
	int		len;
	char	*temp;
	char	**temp_strs;
	t_list	*temp_lst;
	t_list	*next;

	j = 0;
	k = 0;
	len = 0;
	temp = (char*)lst->content;
	while (temp[j] && (temp[j] != '$' || ft_isinsquotes(temp, j)
		|| ft_is_escaped(temp, j)))
		j++;
	len = ft_strlen(key);
	k = (temp[j] == '$') ? k + 1 : k;
	while (temp[j + k] && (temp[j + k] != '$' || ft_is_escaped(temp, j + k)
		|| ft_isinsquotes(temp, j + k)) && (!ft_isalnum(temp[j + k])))
		k++;
	while (temp[j + k])
		j++;
	len += j;
	// ft_lst_add_betw()
	lst->content = ft_strdup_env_var(len, temp, key);
	temp = lst->content;
	temp_strs = ft_split_quote(temp, ' ');
	temp_lst = ft_split_to_lst(temp_strs);
	while (temp_lst)
	{
		next = temp_lst->next;
		ft_lstadd_before(&cmd->argv, temp_lst, lst);
		temp_lst = next;
	}
	ft_lstdel_between(&cmd->argv, lst->content, free);
}

void		ft_replace_env_var(char *av, char *key, t_cmd *cmd, int i)
{
	int		j;
	int		k;
	int		len;

	j = 0;
	k = 0;
	len = 0;
	while (av[j] && (av[j] != '$' || ft_isinsquotes(av, j)
		|| ft_is_escaped(av, j)))
		j++;
	len = ft_strlen(key);
	while (av[j + k] && (av[j + k] != '$' || ft_is_escaped(av, j + k)
		|| ft_isinsquotes(av, j + k)) && (!ft_isalnum(av[j + k])))
		k++;
	while (av[j + k])
		j++;
	len += j;
	cmd->av[i] = ft_strdup_env_var(len, av, key);
}

char		*ft_is_in_env(char *str, t_sh *sh)
{
	char	*tmp;
	int		i;
	t_list	*env;

	i = 1;
	env = *(sh->env);
	while (str[i] && (str[i] != '$' || ft_is_escaped(str, i)
		|| ft_isinsquotes(str, i)) && ft_isalnum(str[i]))
		i++;
	tmp = ft_substr(str, 1, i - 1);
	while (env)
	{
		if (!ft_strncmp("?", tmp, 1))
			return (ft_itoa(sh->ret_cmd));
		else if (ft_strncmp(((t_env*)(env->content))->key, tmp, ft_strlen(tmp)) == 0)
			return (((t_env*)(env->content))->value);
		env = env->next;
	}
	return (NULL);
}

void		ft_check_env_var(t_cmd *cmd, t_sh *sh)
{
	char	*key_val;
	int		i;
	int		j;
	t_list	*temp;
	char	*temp_char;

	i = 0;
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
					ft_replace_env_var_lst(temp, key_val, cmd);
					temp = cmd->argv;
					temp_char = (char*)temp->content;
					j = -1;
				}
			}
			j++;
		}
		temp = temp->next;
	}
	cmd->av = ft_lst_to_split(cmd->argv);
}

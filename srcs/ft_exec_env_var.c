/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_env_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 12:14:46 by alienard          #+#    #+#             */
/*   Updated: 2020/09/17 14:41:41 by alienard         ###   ########.fr       */
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

void		ft_replace_env_var_lst_clean(t_list *lst, t_cmd *cmd)
{
	char	*temp;
	char	**temp_strs;
	t_list	*temp_lst;
	t_list	*next;

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

void		ft_replace_env_var_lst(t_list *lst, char *key, t_cmd *cmd)
{
	int		i[3];
	char	*temp;

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	temp = (char*)lst->content;
	while (temp[i[0]] && (temp[i[0]] != '$' || ft_isinsquotes(temp, i[0])
		|| ft_is_escaped(temp, i[0])))
		i[0]++;
	i[2] = (key) ? ft_strlen(key) : i[2];
	i[1] = (temp[i[0]] == '$') ? i[1] + 1 : i[1];
	while (temp[i[0] + i[1]] && (temp[i[0] + i[1]] != '$'
		|| ft_is_escaped(temp, i[0] + i[1])
		|| ft_isinsquotes(temp, i[0] + i[1]))
		&& (!ft_isalnum(temp[i[0] + i[1]])))
		i[1]++;
	while (temp[i[0] + i[1]])
		i[0]++;
	i[2] += i[0];
	lst->content = ft_strdup_env_var(i[2], temp, key);
	ft_replace_env_var_lst_clean(lst, cmd);
}

void		ft_doreplace_env_var(t_cmd *cmd, t_list **temp,
								char *key_val, char **temp_char)
{
	ft_replace_env_var_lst(*temp, key_val, cmd);
	*temp = cmd->argv;
	*temp_char = (char*)(*temp)->content;
}

void		ft_check_env_var(t_cmd *cmd, t_sh *sh)
{
	char	*key_val;
	int		j;
	t_list	*temp;
	char	*temp_char;

	temp = cmd->argv;
	while (temp && (j = -1))
	{
		temp_char = (char*)temp->content;
		while (temp_char[++j])
		{
			if (temp_char[j] == '$' && !ft_isinsquotes(temp_char, j)
				&& !ft_is_escaped(temp_char, j))
			{
				key_val = NULL;
				key_val = ft_is_in_env(temp_char + j, sh);
				if (key_val && (j = -1))
					ft_doreplace_env_var(cmd, &temp, key_val, &temp_char);
				ft_safe_free((void **)&sh->ret_str);
			}
		}
		temp = temp->next;
	}
}

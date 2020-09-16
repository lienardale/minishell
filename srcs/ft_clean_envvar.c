/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_envvar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 10:13:50 by alienard          #+#    #+#             */
/*   Updated: 2020/09/16 15:26:26 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		ft_iterate_dol(char *str, int *i)
{
	if (!ft_isdigit(str[*i]))
	{
		while (ft_isalnum(str[*i]))
			(*i)++;
	}
	else if (ft_isdigit(str[*i]))
		(*i)++;
}

static size_t	ft_strlen_dol(char *str)
{
	int		i;
	int		len;

	i = -1;
	len = 0;
	while (str[++i])
	{
		if (str[i] != '$')
			len++;
		else if (str[i] == '$')
		{
			if (ft_is_escaped(str, i) || ft_isinsquotes(str, i)
				|| !str[i + 1] || ft_isspace(str[i + 1]) || str[i + 1] == '\\'
				|| (ft_isindquotes(str, i) && !ft_isalnum(str[i + 1])))
				len++;
			i++;
			if (str[i] && ft_isalnum(str[i]) && !ft_isinsquotes(str, i)
				&& !ft_is_escaped(str, i - 1))
				ft_iterate_dol(str, &i);
			i--;
		}
	}
	return (len);
}

static void		ft_strlcpy_dol(char *dst, char *src, int dstsize)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (dstsize > 0 && src[++i] && (j < (dstsize - 1)))
	{
		if (src[i] != '$' && (dst[j] = src[i]))
			j++;
		else if (src[i] == '$')
		{
			if ((ft_is_escaped(src, i) || ft_isinsquotes(src, i)
				|| !src[i + 1] || ft_isspace(src[i + 1]) || src[i + 1] == '\\'
				|| (ft_isindquotes(src, i) && !ft_isalnum(src[i + 1])))
				&& (dst[j] = src[i]))
				j++;
			i++;
			if (src[i] && ft_isalnum(src[i]) && !ft_isinsquotes(src, i)
				&& !ft_is_escaped(src, i - 1))
				ft_iterate_dol(src, &i);
			i--;
		}
	}
	dst[j] = '\0';
}

char			*ft_strdup_clean_envvar(char *tmp_char)
{
	char	*tab;

	if (!(tab = (char *)malloc(sizeof(char) * (ft_strlen_dol(tmp_char) + 1))))
		return (NULL);
	// printf("str:%s\nlen:%zu\n", tmp_char, ft_strlen_dol(tmp_char));
	ft_strlcpy_dol(tab, tmp_char, ft_strlen_dol(tmp_char) + 1);
	free(tmp_char);
	return (tab);
}

void			ft_clean_envvar(t_cmd *cmd)
{
	t_list	*tmp;
	char	*tmp_char;

	tmp = cmd->argv;
	while (tmp)
	{
		tmp_char = (char*)tmp->content;
		tmp->content = ft_strdup_clean_envvar(tmp_char);
		tmp = tmp->next;
	}
	ft_lstdelif_false(&cmd->argv, ft_strlen);
	if (cmd->av)
		ft_free_double_array(cmd->av);
	cmd->av = ft_lst_to_split(cmd->argv);
	// ft_lstclear_env(&cmd->argv);
	// ft_lstclear(&cmd->argv, ft_free_env_lst);
}

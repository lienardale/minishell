/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v0_parse_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdai <cdai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 09:31:04 by cdai              #+#    #+#             */
/*   Updated: 2020/05/12 20:08:38 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

static t_list	*ft_relative_to_abs_path(t_list *lstdest, t_list *lstsrc)
{
	char	*temp;
	t_list	*lst_temp;

	while (lstsrc)
	{
		if (ft_strcmp("..", (char*)lstsrc->content) == 0)
			ft_lstdel_last(lstdest);
		else if (ft_strcmp(".", (char*)lstsrc->content) != 0)
		{
			temp = ft_strdup((char*)lstsrc->content);
			lst_temp = ft_lstnew(temp);
			free(temp);
			ft_lstadd_back(&lstdest, lst_temp);
		}
		lstsrc = lstsrc->next;
	}
	return (lstdest);
}

static char		*ft_get_cwd_lstsplited(char *path)
{
	t_list	*path_splited;
	t_list	*buff_splited;
	char	*result;

	path_splited = ft_lstsplit(path, '/');
	free(path);
	result = ft_calloc(1, 1000);
	getcwd(result, 1000);
	buff_splited = ft_lstsplit(result, '/');
	free(result);
	ft_relative_to_abs_path(buff_splited, path_splited);
	result = ft_lststrjoin(buff_splited, "/");
	ft_lstclear(&buff_splited, free);
	ft_lstclear(&path_splited, free);
	return (result);
}

char			*ft_parse_path(char *path)
{
	char	*temp;
	char	*exec;
	int		start;
	char	*result;

	exec = NULL;
	start = ft_isolate_exec(path, &exec);
	path = ft_substr(path, 0, start);
	result = ft_get_cwd_lstsplited(path);
	temp = result;
	result = ft_strjoin(result, "/");
	free(temp);
	temp = result;
	result = ft_strjoin(result, exec);
	free(temp);
	if (exec)
		free(exec);
	return (result);
}

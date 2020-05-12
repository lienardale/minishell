/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v0_parse_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdai <cdai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 09:31:04 by cdai              #+#    #+#             */
/*   Updated: 2020/05/12 08:40:27 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

static int	ft_is_cwd(char *exec)
{
	if (exec[0] == '.' && (exec[1] == '/' || exec[1] == '\0'))
		return (1);
	return (0);
}

static int	ft_is_parent_dir(char *exec)
{
	int	i;

	i = 0;
	while (exec[i] == '.')
		i++;
	if (i == 2 && (exec[i] == '/' || exec[i] == '\0'))
		return (1);
	return (0);
}

static char	*ft_lst_minishell_join(t_list *lst)
{
	char	*result;
	char	*temp;

	result = 0;
	while(lst)
	{
		if (result)
		{
			temp = result;
			result = ft_strjoin(temp, "/");
			free(temp);
			temp = result;
			result = ft_strjoin(temp, (char*)lst->content);
			free(temp);
		}
		else
			result = ft_strjoin("/", (char*)lst->content);
		lst = lst->next;
	}
	return (result);
}

char		*ft_parse_path(char *exec)
{
	t_list	*exec_splited;
	char	*result;
	char	*buff;
	t_list	*buff_splited;
	int		i;

	i = 0;
	exec_splited = ft_lstsplit(exec, '/');
	buff = ft_calloc(1, 1000);
	getcwd(buff, 1000);
	buff_splited = ft_lstsplit(buff, '/');
result = 0;
/*
	while (exec[i])
	{
		if (ft_is_cwd(exec))
		{
			
		}
		else if (ft_is_parent_dir(exec))
		{

		}
		while (!(exec[i] == '/' || exec[i] == '\0'))
			i++;
		if (exec[i])
			i++;
	}
*/
	result = ft_lst_minishell_join(buff_splited);
	return (result);
}

int main()
{
	char *buff;
	t_list	*splited;
	t_list	*temp_splited;

	buff = ft_calloc(1, 1000);
	printf("from main: %s\n", (buff = getcwd(buff, 50)));
	splited = ft_lstsplit(buff, '/');
	temp_splited = splited;
	while (temp_splited)
	{
		printf("lst value: %s\n", (char*)temp_splited->content);
		temp_splited = temp_splited->next;
	}
	char *test = ft_lst_minishell_join(splited);
	printf("%s\n", test);
	ft_lstclear(&splited, free);
	
	free(buff);
}

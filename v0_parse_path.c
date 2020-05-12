/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v0_parse_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdai <cdai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 09:31:04 by cdai              #+#    #+#             */
/*   Updated: 2020/05/12 17:18:40 by cdai             ###   ########.fr       */
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
//			free(temp);
			ft_lstadd_back(&lstdest, lst_temp);
		}
		lstsrc = lstsrc->next;
	}
	return (lstdest);
}

char		*ft_parse_path(char *path)
{
	t_list	*path_splited;
	char	*result;
	char	*temp;
t_list	*buff_splited;
	char	*exec;
	int		start;



	start = ft_isolate_exec(path, &exec);
path = ft_substr(path, 0, start);
path_splited = ft_lstsplit(path, '/');
free(path);

// maybe do a function for readability.
result = ft_calloc(1, 1000);
getcwd(result, 1000);
buff_splited = ft_lstsplit(result, '/');
free(result);

//	t_list *ft_relative_to_abs_path(t_list *lstdest, t_list *lstsrc);
	ft_relative_to_abs_path(buff_splited, path_splited);
	result = ft_lststrjoin(buff_splited, "/");
	temp = result;
	result = ft_strjoin(result, "/");
	free(temp);
	temp = result;
	result = ft_strjoin(result, exec);
	free(temp);

	free(exec);
	// join de exec
	ft_lstclear(&buff_splited, free);
	ft_lstclear(&path_splited, free);
	return (result);
}
/*
int main()
{
	char *buff;
	t_list	*splited;
	t_list	*temp_splited;

//test getcwd()
	buff = ft_calloc(1, 1000);
//	printf("from main: %s\n", (buff = getcwd(buff, 50)));

//test ft_lstsplit()
	splited = ft_lstsplit(buff, '/');
	temp_splited = splited;
	while (temp_splited)
	{
//		printf("lst value: %s\n", (char*)temp_splited->content);
		temp_splited = temp_splited->next;
	}

//test ft_lst_minishell_join()
	char *test = ft_lststrjoin(splited, "/");
//	printf("%s\n", test);
	free(test);
//test ft_lstclear()
	ft_lstclear(&splited, free);

//test ft_parse_path()
	char *temp = "./test/patate"; 
	test = ft_parse_path(temp);
	printf("ft_parse_path(%s): %s\n", temp, test);
	free(test);
	
	free(buff);
}
*/


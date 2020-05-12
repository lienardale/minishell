/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v0_parse_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdai <cdai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 09:31:04 by cdai              #+#    #+#             */
/*   Updated: 2020/05/12 12:44:12 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

static	int	ft_isolate_exec(char *path, char **buff)
{
	int		path_len;
	int		i;

	path_len = ft_strlen(path);
	i = path_len - 1;
	while (i > -1 && path[i] != '/')
		i--;
	if (i > -1 && path[i] == '/')
		*buff = ft_substr(path, i + 1, path_len - i);
	return (i); 
		// return last '/' position in path
		// return -1 if '/' not found
		// return 0 if path is absolute
}

static t_list	*ft_relative_to_abs_path(t_list *lstdest, t_list *lstsrc)
{
	while (lstsrc)
	{
		if (ft_strcmp("..", (char*)lstsrc->content) == 0)
			ft_lstdel_last(lstdest);
		else if (ft_strcmp(".", (char*)lstsrc->content) != 0)
			ft_lstadd_back(&lstdest, lstsrc);
		lstsrc = lstsrc->next;
	}
}

char		*ft_parse_path(char *path)
{
	t_list	*path_splited;
	char	*result;
t_list	*buff_splited;
	char	*exec;
	int		start;



	start = ft_isolate_exec(path, &exec);
path = ft_substr(path, 0, start - 1);
path_splited = ft_lstsplit(path, '/');
free(path);

// maybe do a function for readability.
result = ft_calloc(1, 1000);
getcwd(result, 1000);
buff_splited = ft_lstsplit(buff, '/');
free(result);

//	t_list *ft_relative_to_abs_path(t_list *lstdest, t_list *lstsrc);
	ft_relative_to_abs_path(buff_splited, path_splited);
	result = ft_lststrjoin(buff_splited, "/");
	// join de exec
	ft_lstclear(&buff_splited, free);
	ft_lstclear(&path_splited, free);
	return (result);
}

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

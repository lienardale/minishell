/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v0_parse_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdai <cdai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 09:31:04 by cdai              #+#    #+#             */
/*   Updated: 2020/05/10 10:14:17 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

int	ft_is_cwd(char *exec)
{
	if (exec[0] == '.' && (exec[1] == '/' || exec[1] == '\0'))
		return (1);
	return (0);
}

int	ft_is_parent_dir(char *exec)
{
	int	i;

	i = 0;
	while (exec[i] == '.')
		i++;
	if (i == 2 && (exec[i] == '/' || exec[i] == '\0')
		return (1);
	return (0);
}

char	*ft_parse_path(char *exec)
{
	char *buff;
	int i;

	i = 0;
	buff = ft_calloc(1, 1000);
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
	return (result);
}

int main()
{
	char *buff;

	buff = ft_calloc(1, 1000);
	printf("from main: %s\n", (buff = getcwd(buff, 50)));
	free(buff);
}

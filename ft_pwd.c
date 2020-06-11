/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdai <cdai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 18:44:40 by cdai              #+#    #+#             */
/*   Updated: 2020/06/11 16:24:49 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

int	ft_pwd(char **args, t_list **env)
{
	char	*cwd;
	int		buff_size;

	buff_size = 1000;
(void)args;
(void)env;
// mettrer PWD=''
	if (!(cwd = ft_calloc(1, buff_size)))
		return (0);
	getcwd(cwd, buff_size);
	ft_putendl_fd(cwd, 0);
	free(cwd);
ft_free_split(args);
	return (1);
}

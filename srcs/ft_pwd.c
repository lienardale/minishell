/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 18:44:40 by cdai              #+#    #+#             */
/*   Updated: 2020/08/11 14:25:12 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

int	ft_pwd(t_cmd *cmd, t_sh *sh)
{
	char	*cwd;
	int		buff_size;

	(void)sh;
	buff_size = 1000;
// mettrer PWD=''
	if (!(cwd = ft_calloc(1, buff_size)))
		return (0);
	getcwd(cwd, buff_size);
	// ft_putendl_fd(cwd, 0);
	ft_printf("%s\n", cwd);
	free(cwd);
	ft_free_split(cmd->av);
	return (0);
}

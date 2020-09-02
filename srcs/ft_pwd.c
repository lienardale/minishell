/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 18:44:40 by cdai              #+#    #+#             */
/*   Updated: 2020/09/02 18:05:19 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_cmd *cmd, t_sh *sh)
{
	char	*cwd;
	int		buff_size;

	(void)sh;
	buff_size = 1000;
// mettre PWD=''
	if (!(cwd = ft_calloc(1, buff_size)))
		return (0);
	getcwd(cwd, buff_size);
	ft_printf("%s\n", cwd);
	free(cwd);
	ft_free_split(cmd->av);
	return (0);
}

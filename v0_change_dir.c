/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v0_change_dir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdai <cdai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 17:10:39 by cdai              #+#    #+#             */
/*   Updated: 2020/05/18 16:27:53 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

int	ft_change_dir(char **args, char **env)
{
	int		chdir_value;

	chdir_value = chdir(args[1]);
	(void)env;
// change oldpwd et pwd dans env
	if (chdir_value)
	{
		ft_putstr_fd("No such file or directory: ", 0);
		ft_putendl_fd(args[1], 0);
		return (1);
	}
	return (1);
}

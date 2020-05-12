/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v0_change_dir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdai <cdai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 17:10:39 by cdai              #+#    #+#             */
/*   Updated: 2020/05/12 18:51:12 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

int	ft_change_dir(char **args)
{
	int		chdir_value;

	chdir_value = chdir(args[1]);
	if (chdir_value)
	{
		ft_putstr_fd("No such file or directory: ", 0);
		ft_putendl_fd(args[1], 0);
		return (0);
	}
	return (1);
}

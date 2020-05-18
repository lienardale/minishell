/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdai <cdai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 17:31:08 by cdai              #+#    #+#             */
/*   Updated: 2020/05/18 17:48:06 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

int	ft_env(char **args, char **env)
{
(void)args;
	while (*env)
	{
		ft_putendl_fd(*env, 0);
		env++;
	}
	return (1);
}
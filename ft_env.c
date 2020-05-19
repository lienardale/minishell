/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdai <cdai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 17:31:08 by cdai              #+#    #+#             */
/*   Updated: 2020/05/19 16:43:37 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

int	ft_env(char **args, char **env)
{
	while (*env)
	{
		if (ft_memchr(*env, '=', ft_strlen(*env)))
			ft_putendl_fd(*env, 0);
		env++;
	}
	ft_free_split(args);
	return (1);
}

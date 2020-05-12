/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdai <cdai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 18:44:40 by cdai              #+#    #+#             */
/*   Updated: 2020/05/12 18:50:05 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

int	ft_pwd(void)
{
	char	*cwd;
	int		buff_size;

	buff_size = 1000;
	if (!(cwd = ft_calloc(1, buff_size)))
		return (0);
	getcwd(cwd, buff_size);
	ft_putendl_fd(cwd, 0);
	free(cwd);
	return (1);
}

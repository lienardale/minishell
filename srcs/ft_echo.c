/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 15:05:06 by alienard          #+#    #+#             */
/*   Updated: 2020/10/28 17:55:31 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_echo(t_cmd *cmd, t_sh *sh)
{
	int		i;
	int		n;
	char	*line;

	(void)sh;
	n = 0;
	i = 1;
	line = NULL;
	while (cmd->av[i] && !ft_strncmp(cmd->av[i], "-n", 2) && (i++))
		n = 1;
	while (cmd->av[i])
	{
		ft_printf("%s", cmd->av[i]);
		i++;
		if (cmd->av[i])
			ft_printf(" ");
	}
	if (!n)
		ft_printf("\n");
	return (0);
}

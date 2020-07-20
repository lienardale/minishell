/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v0_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 15:05:06 by alienard          #+#    #+#             */
/*   Updated: 2020/07/20 11:32:30 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

int		ft_echo(t_cmd *cmd, t_sh *sh)
{
	int		i;
	int		n;
	char	*line;
	int		quotes;

	(void)sh;
	n = 0;
	i = 0;
	quotes = 0;
	line = NULL;
	if (cmd->av[1] && !ft_strncmp(cmd->av[1], "-n", 2))
		n = 1;
// Pour echo, il faudra faire attention au quote, double quote, espace a l'interieur/l'exterieur etc. le parsing doit etre different.
	if (n && cmd->av[2])
	{
		while (cmd->av[2 + i])
		{
			ft_printf("%s", cmd->av[2 + i]);
			i++;
			if (cmd->av[2 + i])
				ft_printf(" ");
		}
	}
	else if (!quotes && cmd->av[1])
	{
		while (cmd->av[1 + i])
		{
			ft_printf("%s", cmd->av[1 + i]);
			i++;
			if (cmd->av[1 + i])
				ft_printf(" ");
		}
	}
	if (!n)
		ft_printf("\n");
	ft_free_double_array(cmd->av);
	return (1);
}

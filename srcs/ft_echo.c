/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 15:05:06 by alienard          #+#    #+#             */
/*   Updated: 2020/09/10 09:55:48 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_echo(t_cmd *cmd, t_sh *sh)
{
	int		i;
	int		n;
	char	*line;
	int		quotes;

	(void)sh;
	n = 0;
	i = 1;
	quotes = 0;
	line = NULL;
	while (cmd->av[i] && !ft_strncmp(cmd->av[i], "-n", 2) && (i++))
		n = 1;
// Pour echo, il faudra faire attention au quote, double quote, espace a l'interieur/l'exterieur etc. le parsing doit etre different.
	while (cmd->av[i])
	{
		ft_printf("%s", cmd->av[i]);
		i++;
		if (cmd->av[i])
			ft_printf(" ");
	}
	if (!n)
		ft_printf("\n");
//	ft_free_double_array(cmd->av);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v0_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 15:05:06 by alienard          #+#    #+#             */
/*   Updated: 2020/07/10 15:14:56 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

int		ft_echo(char **args, t_list **env)
{
	int		i;
	int		n;
	char	*line;
	int		quotes;

	n = 0;
	i = 0;
	quotes = 0;
	line = NULL;
	(void)env;
	if (args[1] && !ft_strncmp(args[1], "-n", 2))
		n = 1;
// Pour echo, il faudra faire attention au quote, double quote, espace a l'interieur/l'exterieur etc. le parsing doit etre different.
	if (n && args[2])
	{
		while (args[2 + i])
		{
			ft_printf("%s", args[2 + i]);
			i++;
			if (args[2 + i])
				ft_printf(" ");
		}
	}
	else if (!quotes && args[1])
	{
		while (args[1 + i])
		{
			ft_printf("%s", args[1 + i]);
			i++;
			if (args[1 + i])
				ft_printf(" ");
		}
	}
	if (!n)
		ft_printf("\n");
	ft_free_double_array(args);
	return (1);
}

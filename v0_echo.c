/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v0_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 15:05:06 by alienard          #+#    #+#             */
/*   Updated: 2020/05/17 19:46:09 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

int		ft_echo(char **args)
{
	int		i;
	int		n;
	char	*line;
	int		quotes;

	n = 0;
	i = 0;
	quotes = 0;
	line = NULL;
	// ft_printf("			-> %s passe bien par la\n", args[0]);
	if (!ft_strncmp(args[1], "-n", 2) && (i += 3))
		n = 1;
	if ((args[1][i] == '\'' || args[1][i] == '\"')
		&& args[1][i] == args[1][ft_strlen(args[1]) - 1])
		quotes = args[1][i];
	if (!quotes)
		ft_printf("%s", args[1] + i);
	else
		write(1, args[1] + i + 1, ft_strlen(args[1] + i + 1) - 1);
	if (!n)
		ft_printf("\n");
	ft_free_double_array(args);
	return (1);
}

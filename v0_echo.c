/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v0_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 15:05:06 by alienard          #+#    #+#             */
/*   Updated: 2020/05/05 17:37:14 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

int		ft_echo(char **args)
{
	int	i;
	int	n;
	char *line;

	n = 0;
	i = 0;
	line = NULL;
	ft_printf("			-> %s passe bien par la\n", args[0]);
	if (!ft_strcmp(args[1], "-n") && (i += 1))
		n = 1;

	while (args[++i])
		ft_printf("%s", args[i]);
	if (!n)
		ft_printf("\n", args[i]);
	return (1);
}
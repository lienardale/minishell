/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v0_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 15:05:06 by alienard          #+#    #+#             */
/*   Updated: 2020/05/06 13:55:37 by alienard         ###   ########.fr       */
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
	if (!ft_strncmp(args[1], "-n", 2) && (i += 3))
		n = 1;
	ft_printf("%s", args[1] + i);
	if (!n)
		ft_printf("\n");
	return (1);
}
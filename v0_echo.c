/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v0_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 15:05:06 by alienard          #+#    #+#             */
/*   Updated: 2020/05/05 14:43:56 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

int		ft_echo(char **args)
{
	int	i;

	i = 0;
	ft_printf("			-> %s passe bien par la\n", args[0]);
	while (args[++i])
		ft_printf("%s\n", args[i]);
	return (1);
}
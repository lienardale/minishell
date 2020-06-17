/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 13:55:25 by alienard          #+#    #+#             */
/*   Updated: 2020/06/16 13:58:33 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

void	ft_free_double_array(char **str)
{
	int		i;

	i = -1;
	while (str[++i])
		(str[i]) ? ft_free_ptr(str[i]) : 0;
	(str) ? ft_free_ptr(str) : 0;
}

void	ft_print_double_array(char **str, char *name)
{
	int		i;

	i = -1;
	while (str[++i])
		ft_printf("%s[%d]:|%s|\n", name, i, str[i]);
}

size_t	ft_double_strlen(char **str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

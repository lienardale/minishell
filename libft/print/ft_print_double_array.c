/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_double_array.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 11:06:24 by alienard          #+#    #+#             */
/*   Updated: 2020/07/23 11:06:51 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_print_double_array(char **str, char *name)
{
	int		i;

	i = -1;
	while (str[++i])
		ft_printf("%s[%d]:|%s|\n", name, i, str[i]);
}

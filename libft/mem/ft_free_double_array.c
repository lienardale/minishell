/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_double_array.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 11:03:24 by alienard          #+#    #+#             */
/*   Updated: 2020/09/21 12:18:34 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_double_array(char **str)
{
	int		i;

	i = -1;
	while (str[++i])
		(str[i]) ? free(str[i]) : 0;
	(str) ? free(str) : 0;
}

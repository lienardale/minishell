/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_double_array.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 11:03:24 by alienard          #+#    #+#             */
/*   Updated: 2020/09/11 14:02:30 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_double_array(char **str)
{
	int		i;

	i = -1;
	// if (!str || !str[0] || !str[0][0])
	// 	return ;
	while (str[++i])
		(str[i]) ? ft_free_ptr(str[i]) : 0;
	(str) ? ft_free_ptr(str) : 0;
}

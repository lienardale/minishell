/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnum.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 18:54:07 by alienard          #+#    #+#             */
/*   Updated: 2020/01/19 19:11:09 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isnum(char *c)
{
	if ((ft_isdigit(c[0])) == 1 || (c[0] == '-' && ft_isdigit(c[1]) == 1))
		return (1);
	return (0);
}

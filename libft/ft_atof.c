/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 18:59:15 by alienard          #+#    #+#             */
/*   Updated: 2020/01/17 15:53:32 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "math.h"

double	ft_atof(const char *str)
{
	int		i;
	int		y;
	int		neg;
	double	ret;

	i = 0;
	y = 1;
	neg = 1;
	ret = 0;
	while (((9 <= str[i] && str[i] <= 13) || str[i] == 32) && str[i])
		i++;
	if ((str[i] == '-' || str[i] == '+') && str[i])
		(str[i++] == '-') ? neg = -neg : 0;
	while (('0' <= str[i] && str[i] <= '9') && str[i])
		ret = ret * 10 + (str[i++] - '0');
	(str[i] == '.') ? i++ : 0;
	while (('0' <= str[i] && str[i] <= '9') && str[i])
	{
		ret += ((str[i] - '0') / pow(10, y));
		i++;
		y++;
	}
	return ((double)(ret * neg));
}

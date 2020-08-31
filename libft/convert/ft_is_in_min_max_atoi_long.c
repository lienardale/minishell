/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_in_min_max_atoi_long.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdai <cdai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 14:50:08 by cdai              #+#    #+#             */
/*   Updated: 2020/07/28 15:23:54 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_in_min_max_atoi_long(const char *str)
{
	int		i;
	long	neg;
	long	ret;
	long	temp;

	i = 0;
	neg = 1;
	ret = 0;
	temp = 0;
	if (!ft_strcmp(str, "-9223372036854775808"))
		return (1);
	while (((9 <= str[i] && str[i] <= 13) || str[i] == 32) && str[i])
		i++;
	if ((str[i] == '-' || str[i] == '+') && str[i])
	{
		(str[i] == '-') ? neg = -neg : 0;
		i++;
	}
	while (('0' <= str[i] && str[i] <= '9') && str[i])
	{
		ret = ret * 10 + (str[i] - '0');
		if (ret < temp)
			return (0);
		temp = ret;
		i++;
	}
	return (1);
}

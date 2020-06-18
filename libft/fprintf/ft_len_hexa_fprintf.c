/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_len_hexa_fprintf.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 22:11:42 by alienard          #+#    #+#             */
/*   Updated: 2020/04/15 16:51:15 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftfprintf.h"

unsigned int	ft_flen_hexa(long long unsigned int a)
{
	unsigned int	len;

	len = 0;
	while (a > 15)
	{
		a = a / 16;
		len++;
	}
	return (len);
}

unsigned int	ft_flen_unsigned(unsigned int a)
{
	unsigned int	len;

	len = 0;
	while (a > 9)
	{
		a = a / 10;
		len++;
	}
	return (len);
}

unsigned int	ft_flen_d(int a)
{
	long			i;
	unsigned int	len;

	len = 0;
	i = a;
	if (a < 0)
	{
		i = -i;
		len++;
	}
	while (i > 9)
	{
		i = i / 10;
		len++;
	}
	return (len);
}

int				ft_fstrlen_s(const char *str)
{
	int i;

	i = 0;
	if (!str)
		return (6);
	while (str[i])
		i++;
	return (i);
}

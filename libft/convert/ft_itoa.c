/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 15:17:17 by alienard          #+#    #+#             */
/*   Updated: 2019/10/12 16:03:53 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_len(long a)
{
	size_t len;

	len = 0;
	if (a < 0)
	{
		a = -a;
		len++;
	}
	while (a > 0)
	{
		a = a / 10;
		len++;
	}
	return (len);
}

char	*ft_tab0(char *tab)
{
	if (!(tab = (char *)malloc(sizeof(char) * 2)))
		return (NULL);
	tab[0] = '0';
	tab[1] = '\0';
	return (tab);
}

char	*ft_itoa(int n)
{
	long	a;
	char	*tab;
	size_t	len;

	a = n;
	len = ft_len(a);
	tab = NULL;
	if (a == 0)
		return (ft_tab0(tab));
	if (!(tab = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	tab[len--] = '\0';
	if (a < 0)
	{
		tab[0] = '-';
		a = -a;
	}
	while (a > 0)
	{
		tab[len] = a % 10 + '0';
		a = a / 10;
		len--;
	}
	return (tab);
}

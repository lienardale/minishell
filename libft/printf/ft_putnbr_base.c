/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 19:50:17 by alienard          #+#    #+#             */
/*   Updated: 2019/12/27 17:32:49 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		ft_putnbr_hexa(long long unsigned int nbr, int r)
{
	long long unsigned int	a;
	char					*base;

	base = "0123456789abcdef";
	a = nbr;
//	a = (nbr < 0) ? -nbr : nbr;
//	(nbr < 0) ? r += write(1, "-", 1) : 0;
	(a > 15) ? r = ft_putnbr_hexa((long long unsigned int)(a / 16), r) : 0;
	r += write(1, &(base[a % 16]), 1);
	return (r);
}

int		ft_putnbr_hexm(long long unsigned int nbr, int r)
{
	long long unsigned int	a;
	char					*base;

	base = "0123456789ABCDEF";
	a = nbr;
//	a = (nbr < 0) ? -nbr : nbr;
//	(nbr < 0) ? r += write(1, "-", 1) : 0;
	(a > 15) ? r = ft_putnbr_hexm((long long unsigned int)(a / 16), r) : 0;
	r += write(1, &(base[a % 16]), 1);
	return (r);
}

int		ft_putnbr_unsigned(unsigned int n, int r)
{
	char			*base;

	base = "0123456789";
//	n = (n < 0) ? -n : n;
	(n > 9) ? r = ft_putnbr_unsigned((n / 10), r) : 0;
	r += write(1, &(base[n % 10]), 1);
	return (r);
}

int		ft_putnbr_dec(int n, int fd)
{
	unsigned int	a;
	char			*base;

	base = "0123456789";
	a = (n > 0) ? n : -n;
	(n < 0) ? fd += write(1, "-", 1) : 0;
	(a > 9) ? fd = ft_putnbr_dec((int)(a / 10), fd) : 0;
	fd += write(1, &(base[a % 10]), 1);
	return (fd);
}

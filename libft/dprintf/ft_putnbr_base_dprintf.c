/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_dprintf.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 19:50:17 by alienard          #+#    #+#             */
/*   Updated: 2020/04/15 16:42:15 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftdprintf.h"

int		ft_dputnbr_hexa(t_dool *fl, long long unsigned int nbr, int r)
{
	long long unsigned int	a;
	char					*base;

	base = "0123456789abcdef";
	a = (nbr < 0) ? -nbr : nbr;
	(nbr < 0) ? r += write(fl->fd, "-", 1) : 0;
	(a > 15) ? r = ft_dputnbr_hexa(fl, (long long unsigned int)(a / 16), r) : 0;
	r += write(fl->fd, &(base[a % 16]), 1);
	return (r);
}

int		ft_dputnbr_hexm(t_dool *fl, long long unsigned int nbr, int r)
{
	long long unsigned int	a;
	char					*base;

	base = "0123456789ABCDEF";
	a = (nbr < 0) ? -nbr : nbr;
	(nbr < 0) ? r += write(fl->fd, "-", 1) : 0;
	(a > 15) ? r = ft_dputnbr_hexm(fl, (long long unsigned int)(a / 16), r) : 0;
	r += write(fl->fd, &(base[a % 16]), 1);
	return (r);
}

int		ft_dputnbr_unsigned(t_dool *fl, unsigned int n, int r)
{
	char			*base;

	base = "0123456789";
	n = (n < 0) ? -n : n;
	(n > 9) ? r = ft_dputnbr_unsigned(fl, (n / 10), r) : 0;
	r += write(fl->fd, &(base[n % 10]), 1);
	return (r);
}

int		ft_dputnbr_dec(t_dool *fl, int n, int fd)
{
	unsigned int	a;
	char			*base;

	base = "0123456789";
	a = (n > 0) ? n : -n;
	(n < 0) ? fd += write(fl->fd, "-", 1) : 0;
	(a > 9) ? fd = ft_dputnbr_dec(fl, (int)(a / 10), fd) : 0;
	fd += write(fl->fd, &(base[a % 10]), 1);
	return (fd);
}

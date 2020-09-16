/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_fprintf.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 19:50:17 by alienard          #+#    #+#             */
/*   Updated: 2020/09/16 17:24:33 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftfprintf.h"

int		ft_fputnbr_hexa(t_fool *fl, long long unsigned int nbr, int r)
{
	long long unsigned int	a;
	char					*base;

	base = "0123456789abcdef";
	a = nbr;
	(a > 15) ? r = ft_fputnbr_hexa(fl, (long long unsigned int)(a / 16), r) : 0;
	r += fwrite(&(base[a % 16]), sizeof(char), 1, fl->file);
	return (r);
}

int		ft_fputnbr_hexm(t_fool *fl, long long unsigned int nbr, int r)
{
	long long unsigned int	a;
	char					*base;

	base = "0123456789ABCDEF";
	a = nbr;
	(a > 15) ? r = ft_fputnbr_hexm(fl, (long long unsigned int)(a / 16), r) : 0;
	r += fwrite(&(base[a % 16]), sizeof(char), 1, fl->file);
	return (r);
}

int		ft_fputnbr_unsigned(t_fool *fl, unsigned int n, int r)
{
	char			*base;

	base = "0123456789";
	(n > 9) ? r = ft_fputnbr_unsigned(fl, (n / 10), r) : 0;
	r += fwrite(&(base[n % 10]), sizeof(char), 1, fl->file);
	return (r);
}

int		ft_fputnbr_dec(t_fool *fl, int n, int fd)
{
	unsigned int	a;
	char			*base;

	base = "0123456789";
	a = (n > 0) ? n : -n;
	(n < 0) ? fd += fwrite("-", sizeof(char), 1, fl->file) : 0;
	(a > 9) ? fd = ft_fputnbr_dec(fl, (int)(a / 10), fd) : 0;
	fd += fwrite(&(base[a % 10]), sizeof(char), 1, fl->file);
	return (fd);
}

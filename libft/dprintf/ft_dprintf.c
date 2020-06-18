/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 17:32:54 by alienard          #+#    #+#             */
/*   Updated: 2020/04/15 17:43:51 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftdprintf.h"

t_dool	ft_dfl_init(int fd)
{
	t_dool	tmp;

	tmp.fd = fd;
	tmp.prct = -1;
	tmp.lpad = 0;
	tmp.fpad = ' ';
	tmp.preci = -1;
	tmp.lpreci = 0;
	tmp.neg = -1;
	tmp.conv = 0;
	tmp.c = 0;
	tmp.s = "(null)";
	tmp.p = NULL;
	tmp.d = 0;
	tmp.u = 0;
	return (tmp);
}

int		ft_dorder(t_dool *fl, char tab, int r)
{
	if (tab == 'c')
		return (ft_dc(fl, tab, r));
	if (fl->neg == 0 && fl->preci == 0)
		(fl->lpreci)++;
	if (fl->fpad != '-')
	{
		r = ft_dprint_lpad(fl, r);
		if (tab != 's' && tab != 'p')
			r = ft_dprint_preci(fl, r);
		r = ft_dprint_conv(fl, tab, r);
		return (r);
	}
	else
	{
		if (tab != 's' && tab != 'p')
			r = ft_dprint_preci(fl, r);
		r = ft_dprint_conv(fl, tab, r);
		r = ft_dprint_lpad(fl, r);
		return (r);
	}
	return (r);
}

int		ft_dprct(int *y, t_dool *fl, int r)
{
	fl->c = '%';
	fl->conv = 'c';
	r = ft_dorder(fl, 'c', r);
	fl->prct = 0;
	*y = *y + 1;
	return (r);
}

int		ft_dprintf(int fd, const char *tab, ...)
{
	va_list	ap;
	t_dool	fl;
	int		y;
	int		r;

	va_start(ap, tab);
	r = 0;
	y = 0;
	while (tab[y] != '\0' && y < (int)ft_dstrlen_s(tab))
	{
		fl = ft_dfl_init(fd);
		while (tab[y] && tab[y] != '%')
			r += write(fl.fd, &tab[y++], 1);
		fl.prct = (tab[y++] == '%') ? 1 : -1;
		if (fl.prct == 1 && (y = ft_dlpad_init(y, tab, ap, &fl)))
			y = ft_dpreci_init(y, tab, ap, &fl);
		if (tab[y] && tab[y] == '%' && fl.prct == 1)
			r = ft_dprct(&y, &fl, r);
		r = (fl.prct == 1) ? ft_dconv_init(&fl, tab[y++], ap, r) : r;
	}
	va_end(ap);
	return (r);
}

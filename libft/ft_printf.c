/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 10:20:49 by alienard          #+#    #+#             */
/*   Updated: 2020/01/06 13:53:01 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

t_bool	ft_fl_init(void)
{
	t_bool fl;

	fl.prct = -1;
	fl.lpad = 0;
	fl.fpad = ' ';
	fl.preci = -1;
	fl.lpreci = 0;
	fl.neg = -1;
	fl.conv = 0;
	fl.c = 0;
	fl.s = "(null)";
	fl.p = NULL;
	fl.d = 0;
	fl.u = 0;
	return (fl);
}

int		ft_order(t_bool *fl, char tab, int r)
{
	if (tab == 'c')
		return (ft_c(fl, tab, r));
	if (fl->neg == 0 && fl->preci == 0)
		(fl->lpreci)++;
	if (fl->fpad != '-')
	{
		r = ft_print_lpad(fl, r);
		if (tab != 's' && tab != 'p')
			r = ft_print_preci(fl, r);
		r = ft_print_conv(fl, tab, r);
		return (r);
	}
	else
	{
		if (tab != 's' && tab != 'p')
			r = ft_print_preci(fl, r);
		r = ft_print_conv(fl, tab, r);
		r = ft_print_lpad(fl, r);
		return (r);
	}
	return (r);
}

int		ft_prct(int *y, t_bool *fl, int r)
{
	fl->c = '%';
	fl->conv = 'c';
	r = ft_order(fl, 'c', r);
	fl->prct = 0;
	*y = *y + 1;
	return (r);
}

int		ft_printf(const char *tab, ...)
{
	va_list	ap;
	t_bool	fl;
	int		y;
	int		r;

	va_start(ap, tab);
	r = 0;
	y = 0;
	while (tab[y] != '\0' && y < (int)ft_strlen_s(tab))
	{
		fl = ft_fl_init();
		while (tab[y] && tab[y] != '%')
			r += write(1, &tab[y++], 1);
		fl.prct = (tab[y++] == '%') ? 1 : -1;
		if (fl.prct == 1 && (y = ft_lpad_init(y, tab, ap, &fl)))
			y = ft_preci_init(y, tab, ap, &fl);
		if (tab[y] && tab[y] == '%' && fl.prct == 1)
			r = ft_prct(&y, &fl, r);
		r = (fl.prct == 1) ? ft_conv_init(&fl, tab[y++], ap, r) : r;
	}
	va_end(ap);
	return (r);
}

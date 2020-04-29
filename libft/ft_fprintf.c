/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 10:20:49 by alienard          #+#    #+#             */
/*   Updated: 2020/04/15 17:31:07 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftfprintf.h"

t_fool	ft_ffl_init(FILE *file)
{
	t_fool fl;

	fl.file = file;
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

int		ft_forder(t_fool *fl, char tab, int r)
{
	if (tab == 'c')
		return (ft_fc(fl, tab, r));
	if (fl->neg == 0 && fl->preci == 0)
		(fl->lpreci)++;
	if (fl->fpad != '-')
	{
		r = ft_fprint_lpad(fl, r);
		if (tab != 's' && tab != 'p')
			r = ft_fprint_preci(fl, r);
		r = ft_fprint_conv(fl, tab, r);
		return (r);
	}
	else
	{
		if (tab != 's' && tab != 'p')
			r = ft_fprint_preci(fl, r);
		r = ft_fprint_conv(fl, tab, r);
		r = ft_fprint_lpad(fl, r);
		return (r);
	}
	return (r);
}

int		ft_fprct(int *y, t_fool *fl, int r)
{
	fl->c = '%';
	fl->conv = 'c';
	r = ft_forder(fl, 'c', r);
	fl->prct = 0;
	*y = *y + 1;
	return (r);
}

int		ft_fprintf(FILE *stream, const char *tab, ...)
{
	va_list	ap;
	t_fool	fl;
	int		y;
	int		r;

	va_start(ap, tab);
	r = 0;
	y = 0;
	while (tab[y] != '\0' && y < (int)ft_fstrlen_s(tab))
	{
		fl = ft_ffl_init(stream);
		while (tab[y] && tab[y] != '%')
			r += fwrite(&tab[y++], sizeof(char), 1, fl.file);
		fl.prct = (tab[y++] == '%') ? 1 : -1;
		if (fl.prct == 1 && (y = ft_flpad_init(y, tab, ap, &fl)))
			y = ft_fpreci_init(y, tab, ap, &fl);
		if (tab[y] && tab[y] == '%' && fl.prct == 1)
			r = ft_fprct(&y, &fl, r);
		r = (fl.prct == 1) ? ft_fconv_init(&fl, tab[y++], ap, r) : r;
	}
	va_end(ap);
	return (r);
}

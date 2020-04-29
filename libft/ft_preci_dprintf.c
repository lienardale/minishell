/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_preci_dprintf.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 17:47:19 by alienard          #+#    #+#             */
/*   Updated: 2020/04/15 16:42:13 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftdprintf.h"

int	ft_dpreci_init(int y, const char *tab, va_list ap, t_dool *fl)
{
	if (tab[y] && tab[y] == '.' && (y++))
		fl->preci = 0;
	if (fl->preci == 0 && (ft_isdigit(tab[y])) == 1)
		fl->lpreci = ft_atoi(&tab[y]);
	while (tab[y] && (ft_isdigit(tab[y]) == 1))
		y++;
	if (tab[y] && fl->preci == 0 && tab[y] == '*')
	{
		fl->lpreci = va_arg(ap, int);
		if (fl->lpreci < 0)
		{
			fl->lpreci = -1;
			fl->preci = -1;
			y++;
			return (y);
		}
		y++;
	}
	if (fl->preci == 0 && fl->fpad == '0')
		fl->fpad = ' ';
	return (y);
}

int	ft_dprint_preci(t_dool *fl, int r)
{
	int len;
	int n;

	len = ft_dlen_conv(0, fl);
	n = 0;
	if (fl->preci == 0)
	{
		if (fl->neg == 0 && fl->lpreci > len)
		{
			(fl->d < 0) ? r += write(fl->fd, "-", 1) : 0;
			fl->d = (fl->d < 0) ? -(fl->d) : (fl->d);
			fl->neg = 2;
		}
		n = fl->lpreci;
		while (n > len)
		{
			r += write(fl->fd, "0", 1);
			n--;
		}
	}
	return (r);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_preci_fprintf.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 17:47:19 by alienard          #+#    #+#             */
/*   Updated: 2020/04/15 17:06:42 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftfprintf.h"

int	ft_fpreci_init(int y, const char *tab, va_list ap, t_fool *fl)
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

int	ft_fprint_preci(t_fool *fl, int r)
{
	int len;
	int n;

	len = ft_flen_conv(0, fl);
	n = 0;
	if (fl->preci == 0)
	{
		if (fl->neg == 0 && fl->lpreci > len)
		{
			(fl->d < 0) ? r += fwrite("-", sizeof(char), 1, fl->file) : 0;
			fl->d = (fl->d < 0) ? -(fl->d) : (fl->d);
			fl->neg = 2;
		}
		n = fl->lpreci;
		while (n > len)
		{
			r += fwrite("0", sizeof(char), 1, fl->file);
			n--;
		}
	}
	return (r);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_preci.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 17:47:19 by alienard          #+#    #+#             */
/*   Updated: 2019/12/27 16:09:04 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ft_preci_init(int y, const char *tab, va_list ap, t_bool *fl)
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

int	ft_print_preci(t_bool *fl, int r)
{
	int len;
	int n;

	len = ft_len_conv(0, fl);
	n = 0;
	if (fl->preci == 0)
	{
		if (fl->neg == 0 && fl->lpreci > len)
		{
			(fl->d < 0) ? r += write(1, "-", 1) : 0;
			fl->d = (fl->d < 0) ? -(fl->d) : (fl->d);
			fl->neg = 2;
		}
		n = fl->lpreci;
		while (n > len)
		{
			r += write(1, "0", 1);
			n--;
		}
	}
	return (r);
}

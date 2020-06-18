/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_padding_dprintf.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 10:23:36 by alienard          #+#    #+#             */
/*   Updated: 2020/04/15 16:42:11 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftdprintf.h"

int		ft_dlpad_init(int y, const char *tab, va_list ap, t_dool *fl)
{
	while (tab[y] && ft_dis_conv(tab[y]) != 1 && tab[y] != '.')
	{
		if (tab[y] == '0' && (y++))
			fl->fpad = '0';
		if (ft_isdigit(tab[y]) == 1)
			fl->lpad = ft_atoi(&tab[y]);
		while (tab[y] && (ft_isdigit(tab[y]) == 1))
			y++;
		if (tab[y] == '-')
		{
			fl->fpad = '-';
			y++;
		}
		if (ft_isdigit(tab[y]) == 1)
			fl->lpad = ft_atoi(&tab[y]);
		while (tab[y] && (ft_isdigit(tab[y]) == 1))
			y++;
		if (tab[y] == '*')
			ft_dpad_st(&y, ap, fl);
	}
	return (y);
}

void	ft_dpad_st(int *y, va_list ap, t_dool *fl)
{
	fl->lpad = va_arg(ap, int);
	if (fl->lpad < 0)
	{
		fl->fpad = '-';
		fl->lpad = -(fl->lpad);
	}
	*y = *y + 1;
}

int		ft_dprint_lpad(t_dool *fl, int r)
{
	int len;
	int i;

	len = ft_dlen_conv(0, fl);
	if (fl->preci == 0 && fl->conv != 'c')
		len = ft_dlen_preci(len, fl);
	i = fl->lpad;
	if (fl->lpad != 0)
	{
		if (fl->neg == 0 && fl->fpad == '0')
		{
			(fl->d < 0) ? r += write(fl->fd, "-", 1) : 0;
			fl->d = (fl->d < 0) ? -(fl->d) : (fl->d);
			fl->neg = 1;
		}
		while (i > len)
		{
			if (fl->fpad == '0')
				r += write(fl->fd, "0", 1);
			else
				r += write(fl->fd, " ", 1);
			i--;
		}
	}
	return (r);
}

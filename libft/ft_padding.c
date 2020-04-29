/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_padding.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 10:23:36 by alienard          #+#    #+#             */
/*   Updated: 2020/01/07 20:19:26 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		ft_lpad_init(int y, const char *tab, va_list ap, t_bool *fl)
{
	while (tab[y] && ft_is_conv(tab[y]) != 1 && tab[y] != '.')
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
			ft_pad_st(&y, ap, fl);
	}
	return (y);
}

void	ft_pad_st(int *y, va_list ap, t_bool *fl)
{
	fl->lpad = va_arg(ap, int);
	if (fl->lpad < 0)
	{
		fl->fpad = '-';
		fl->lpad = -(fl->lpad);
	}
	*y = *y + 1;
}

int		ft_print_lpad(t_bool *fl, int r)
{
	int len;
	int i;

	len = ft_len_conv(0, fl);
	if (fl->preci == 0 && fl->conv != 'c')
		len = ft_len_preci(len, fl);
	i = fl->lpad;
	if (fl->lpad != 0)
	{
		if (fl->neg == 0 && fl->fpad == '0')
		{
			(fl->d < 0) ? r += write(1, "-", 1) : 0;
			fl->d = (fl->d < 0) ? -(fl->d) : (fl->d);
			fl->neg = 1;
		}
		while (i > len)
		{
			if (fl->fpad == '0')
				r += write(1, "0", 1);
			else
				r += write(1, " ", 1);
			i--;
		}
	}
	return (r);
}

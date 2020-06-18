/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_2_dprintf.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 17:51:47 by alienard          #+#    #+#             */
/*   Updated: 2020/04/15 16:42:04 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftdprintf.h"

int		ft_ds(t_dool *fl, int r)
{
	int		i;
	char	*tab;

	tab = (char *)fl->s;
	if (tab == NULL)
		tab = "(null)";
	i = 0;
	if (fl->preci == -1)
	{
		while (tab[i])
		{
			r += write(fl->fd, &tab[i], 1);
			i++;
		}
	}
	else if (fl->preci == 0 && fl->lpreci == 0)
		return (r);
	i = 0;
	while (tab[i] && i < fl->lpreci)
	{
		r += write(fl->fd, &tab[i], 1);
		i++;
	}
	return (r);
}

int		ft_dp(t_dool *fl, int r)
{
	r += write(fl->fd, "0", 1);
	r += write(fl->fd, "x", 1);
	if (fl->p != NULL || fl->lpad > 0 || fl->preci == -1
			|| (fl->preci == 0 && fl->lpreci != -1))
		r = ft_dputnbr_hexa(fl, (long long unsigned int)fl->p, r);
	while (fl->p == NULL && fl->lpreci > 1)
	{
		r += write(fl->fd, "0", 1);
		(fl->lpreci)--;
	}
	return (r);
}

int		ft_dc(t_dool *fl, char tab, int r)
{
	if (fl->fpad != '-')
	{
		r = ft_dprint_lpad(fl, r);
		r = ft_dprint_conv(fl, tab, r);
		return (r);
	}
	else
	{
		r = ft_dprint_conv(fl, tab, r);
		r = ft_dprint_lpad(fl, r);
		return (r);
	}
}

int		ft_dlen_preci(int len, t_dool *fl)
{
	if (fl->conv == 's' && fl->lpreci < len)
		len = fl->lpreci;
	if (fl->conv != 's' && fl->lpreci > len)
		len = fl->lpreci;
	if (ft_dall_null(fl) == 1 && fl->lpreci == 0)
		len--;
	if (fl->neg == 2)
		len++;
	return (len);
}

int		ft_dlen_conv(int len, t_dool *fl)
{
	if (fl->conv == 'c')
		len = 1;
	else if (fl->conv == 's')
		len = (int)ft_dstrlen_s(fl->s);
	else if (fl->conv == 'p')
		len = ft_dlen_hexa((long long unsigned int)fl->p) + 3;
	else if (fl->conv == 'x')
		len = ft_dlen_hexa((long long unsigned int)fl->u) + 1;
	else if (fl->conv == 'X')
		len = ft_dlen_hexa((long long unsigned int)fl->u) + 1;
	else if (fl->conv == 'd')
		len = ft_dlen_d(fl->d) + 1;
	else if (fl->conv == 'u')
		len = ft_dlen_unsigned(fl->u) + 1;
	return (len);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_2_fprintf.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 17:51:47 by alienard          #+#    #+#             */
/*   Updated: 2020/04/15 17:09:02 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftfprintf.h"

int		ft_fs(t_fool *fl, int r)
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
			r += fwrite(&tab[i], sizeof(char), 1, fl->file);
			i++;
		}
	}
	else if (fl->preci == 0 && fl->lpreci == 0)
		return (r);
	i = 0;
	while (tab[i] && i < fl->lpreci)
	{
		r += fwrite(&tab[i], sizeof(char), 1, fl->file);
		i++;
	}
	return (r);
}

int		ft_fp(t_fool *fl, int r)
{
	r += fwrite("0", sizeof(char), 1, fl->file);
	r += fwrite("x", sizeof(char), 1, fl->file);
	if (fl->p != NULL || fl->lpad > 0 || fl->preci == -1
			|| (fl->preci == 0 && fl->lpreci != -1))
		r = ft_fputnbr_hexa(fl, (long long unsigned int)fl->p, r);
	while (fl->p == NULL && fl->lpreci > 1)
	{
		r += fwrite("0", sizeof(char), 1, fl->file);
		(fl->lpreci)--;
	}
	return (r);
}

int		ft_fc(t_fool *fl, char tab, int r)
{
	if (fl->fpad != '-')
	{
		r = ft_fprint_lpad(fl, r);
		r = ft_fprint_conv(fl, tab, r);
		return (r);
	}
	else
	{
		r = ft_fprint_conv(fl, tab, r);
		r = ft_fprint_lpad(fl, r);
		return (r);
	}
}

int		ft_flen_preci(int len, t_fool *fl)
{
	if (fl->conv == 's' && fl->lpreci < len)
		len = fl->lpreci;
	if (fl->conv != 's' && fl->lpreci > len)
		len = fl->lpreci;
	if (ft_fall_null(fl) == 1 && fl->lpreci == 0)
		len--;
	if (fl->neg == 2)
		len++;
	return (len);
}

int		ft_flen_conv(int len, t_fool *fl)
{
	if (fl->conv == 'c')
		len = 1;
	else if (fl->conv == 's')
		len = (int)ft_fstrlen_s(fl->s);
	else if (fl->conv == 'p')
		len = ft_flen_hexa((long long unsigned int)fl->p) + 3;
	else if (fl->conv == 'x')
		len = ft_flen_hexa((long long unsigned int)fl->u) + 1;
	else if (fl->conv == 'X')
		len = ft_flen_hexa((long long unsigned int)fl->u) + 1;
	else if (fl->conv == 'd')
		len = ft_flen_d(fl->d) + 1;
	else if (fl->conv == 'u')
		len = ft_flen_unsigned(fl->u) + 1;
	return (len);
}

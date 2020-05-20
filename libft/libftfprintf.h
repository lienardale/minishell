/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftfprintf.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 10:06:39 by alienard          #+#    #+#             */
/*   Updated: 2020/05/20 13:56:59 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTFPRINTF_H
# define LIBFTFPRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include "libft.h"

typedef struct	s_fool
{
	FILE			*file;
	int				prct;
	int				fpad;
	int				lpad;
	int				preci;
	int				lpreci;
	int				neg;
	int				conv;
	int				c;
	char			*s;
	void			*p;
	int				d;
	unsigned int	u;
}				t_fool;

t_fool			ft_ffl_init(FILE *file);
int				ft_fis_conv(char i);
int				ft_fconv_init(t_fool *fl, char tab, va_list ap, int r);
int				ft_fprint_conv(t_fool *fl, char tab, int r);
int				ft_forder(t_fool *fl, char tab, int r);
int				ft_fprintf(FILE *stream, const char *tab, ...);
int				ft_fprct(int *y, t_fool *fl, int r);
int				ft_fall_null(t_fool *fl);
int				ft_flpad_init(int y, const char *tab, va_list ap, t_fool *fl);
void			ft_fpad_st(int *y, va_list ap, t_fool *fl);
int				ft_fpreci_init(int y, const char *tab, va_list ap, t_fool *fl);
int				ft_fprint_lpad(t_fool *fl, int r);
int				ft_fprint_preci(t_fool *fl, int r);
int				ft_fputnbr_hexa(t_fool *fl, long long unsigned int nbr, int r);
int				ft_fputnbr_hexm(t_fool *fl, long long unsigned int nbr, int r);
int				ft_fputnbr_unsigned(t_fool *fl, unsigned int n, int r);
int				ft_fputnbr_dec(t_fool *fl, int n, int fd);
int				ft_fs(t_fool *fl, int r);
int				ft_fp(t_fool *fl, int r);
int				ft_fc(t_fool *fl, char tab, int r);
unsigned int	ft_flen_hexa(long long unsigned int a);
unsigned int	ft_flen_unsigned(unsigned int a);
unsigned int	ft_flen_d(int a);
int				ft_fstrlen_s(const char *str);
int				ft_flen_conv(int len, t_fool *fl);
int				ft_flen_preci(int len, t_fool *fl);

#endif

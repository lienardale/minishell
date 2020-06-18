/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 10:06:39 by alienard          #+#    #+#             */
/*   Updated: 2020/05/20 13:56:37 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

typedef struct	s_bool
{
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
}				t_bool;

t_bool			ft_fl_init();
int				ft_is_conv(char i);
int				ft_conv_init(t_bool *fl, char tab, va_list ap, int r);
int				ft_print_conv(t_bool *fl, char tab, int r);
int				ft_order(t_bool *fl, char tab, int r);
int				ft_printf(const char *tab, ...);
int				ft_prct(int *y, t_bool *fl, int r);
int				ft_all_null(t_bool *fl);
int				ft_lpad_init(int y, const char *tab, va_list ap, t_bool *fl);
void			ft_pad_st(int *y, va_list ap, t_bool *fl);
int				ft_preci_init(int y, const char *tab, va_list ap, t_bool *fl);
int				ft_print_lpad(t_bool *fl, int r);
int				ft_print_preci(t_bool *fl, int r);
int				ft_putnbr_hexa(long long unsigned int nbr, int r);
int				ft_putnbr_hexm(long long unsigned int nbr, int r);
int				ft_putnbr_unsigned(unsigned int n, int r);
int				ft_putnbr_dec(int n, int fd);
int				ft_s(t_bool *fl, int r);
int				ft_p(t_bool *fl, int r);
int				ft_c(t_bool *fl, char tab, int r);
unsigned int	ft_len_hexa(long long unsigned int a);
unsigned int	ft_len_unsigned(unsigned int a);
unsigned int	ft_len_d(int a);
int				ft_strlen_s(const char *str);
int				ft_len_conv(int len, t_bool *fl);
int				ft_len_preci(int len, t_bool *fl);

#endif

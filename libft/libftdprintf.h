/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftdprintf.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 10:06:39 by alienard          #+#    #+#             */
/*   Updated: 2020/04/15 16:42:43 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTDPRINTF_H
# define LIBFTDPRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft.h"
# include "get_next_line_bonus.h"

typedef struct	s_dool
{
	int				fd;
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
}				t_dool;

t_dool			ft_dfl_init(int fd);
int				ft_dis_conv(char i);
int				ft_dconv_init(t_dool *fl, char tab, va_list ap, int r);
int				ft_dprint_conv(t_dool *fl, char tab, int r);
int				ft_dorder(t_dool *fl, char tab, int r);
int				ft_dprintf(int fd, const char *tab, ...);
int				ft_dprct(int *y, t_dool *fl, int r);
int				ft_dall_null(t_dool *fl);
int				ft_dlpad_init(int y, const char *tab, va_list ap, t_dool *fl);
void			ft_dpad_st(int *y, va_list ap, t_dool *fl);
int				ft_dpreci_init(int y, const char *tab, va_list ap, t_dool *fl);
int				ft_dprint_lpad(t_dool *fl, int r);
int				ft_dprint_preci(t_dool *fl, int r);
int				ft_dputnbr_hexa(t_dool *fl, long long unsigned int nbr, int r);
int				ft_dputnbr_hexm(t_dool *fl, long long unsigned int nbr, int r);
int				ft_dputnbr_unsigned(t_dool *fl, unsigned int n, int r);
int				ft_dputnbr_dec(t_dool *fl, int n, int fd);
int				ft_ds(t_dool *fl, int r);
int				ft_dp(t_dool *fl, int r);
int				ft_dc(t_dool *fl, char tab, int r);
unsigned int	ft_dlen_hexa(long long unsigned int a);
unsigned int	ft_dlen_unsigned(unsigned int a);
unsigned int	ft_dlen_d(int a);
int				ft_dstrlen_s(const char *str);
int				ft_dlen_conv(int len, t_dool *fl);
int				ft_dlen_preci(int len, t_dool *fl);

#endif

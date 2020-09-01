/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 14:16:55 by cdai              #+#    #+#             */
/*   Updated: 2020/09/01 10:36:00 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

static void	ft_strl_c_off(int sig)
{
	(void)sig;
}

static void	ft_ctrl_c_on(int sig)
{
	(void)sig;
	write(0, "\nminishell$ ", 12);
}

static void	ft_ctrl_backslash_off(int sig)
{
	(void)sig;
}

static void	ft_ctrl_backslash_on(int sig)
{
	(void)sig;
	write(1, "\b\b  ", 4);
	write(1, "\b\b", 2);
}

void		ft_signal(int sig, int is_on)
{
	if (is_on)
	{
		if (sig == SIGQUIT)
			signal(sig, ft_ctrl_backslash_on);
		else if (sig == SIGINT)
			signal(sig, ft_ctrl_c_on);
	}
	else
	{
		if (sig == SIGQUIT)
			signal(sig, ft_ctrl_backslash_off);
		else if (sig == SIGINT)
			signal(sig, ft_strl_c_off);
	}
}

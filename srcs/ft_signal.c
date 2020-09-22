/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 14:16:55 by cdai              #+#    #+#             */
/*   Updated: 2020/09/22 08:28:07 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_strl_c_off(int sig)
{
	(void)sig;
}

static void	ft_ctrl_c_on(int sig)
{
	(void)sig;
	write(2, "\nminishell$ ", 12);
	g_sh.sig = false;
	
			(g_sh.begin_input) ? ft_lstclear(&g_sh.begin_input, &free) : 0;
			ft_reset_sh(&g_sh);
//			free(g_sh.line);
//			g_sh.line = NULL;
			g_sh.begin_input = NULL;
}

static void	ft_ctrl_backslash_off(int sig)
{
	(void)sig;
}

static void	ft_ctrl_backslash_on(int sig)
{
	(void)sig;
	write(2, "\b\b  ", 4);
	write(2, "\b\b", 2);
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

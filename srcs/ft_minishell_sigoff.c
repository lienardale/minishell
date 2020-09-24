/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_sigoff.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 19:00:23 by alienard          #+#    #+#             */
/*   Updated: 2020/09/23 19:02:18 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_strl_c_off(int sig)
{
	(void)sig;
}

static void	ft_ctrl_backslash_off(int sig)
{
	(void)sig;
}

void		ft_minishell_sigoff(void)
{
	signal(SIGQUIT, ft_ctrl_backslash_off);
	signal(SIGINT, ft_strl_c_off);
}

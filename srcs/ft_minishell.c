/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 13:06:27 by alienard          #+#    #+#             */
/*   Updated: 2020/09/23 18:55:58 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sh	g_sh;

int	main(int ac, char **av, char **env)
{
	t_list			*env_lst;
	static int		(*builtin_fct[])(t_cmd *, t_sh *) = {
									&ft_echo, &ft_pwd, &ft_env, &ft_export};
	int				fd;

	env_lst = NULL;
	fd = 0;
	if (!(env_lst = ft_start_minishell(env)))
		return (EXIT_FAILURE);
	g_sh = (t_sh) {
			.fd = fd, .nbline = 0, .file = NULL, .line = NULL, .ret_cmd = 0,
			.ret_str = NULL, .ret_sh = 1, .blt_fct = builtin_fct,
			.cmds = NULL, .env = &env_lst, .begin_input = NULL, .sig = true};
	if (ac != 1 && (g_sh.file = av[1]))
	{
		g_sh.fd = open(av[1], O_RDONLY);
		ft_infile(&g_sh);
	}
	else
		ft_prompt(&g_sh);
	if (fd != STDIN_FILENO && close(fd) < 0
		&& ft_dprintf(2, "Close of fd in main not ok\n"))
		return (1);
	return (g_sh.ret_sh);
}

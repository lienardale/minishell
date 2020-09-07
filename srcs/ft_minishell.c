/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 13:06:27 by alienard          #+#    #+#             */
/*   Updated: 2020/09/07 18:40:36 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_list			*env_lst;
	static int		(*builtin_fct[])(t_cmd *, t_sh *) = {BUILTINS};
	int				fd;
	t_sh			sh;

	env_lst = NULL;
	fd = 0;
	if (!(env_lst = ft_start_minishell(env)))
		return (EXIT_FAILURE);
	sh = (t_sh) {
			.fd = fd, .nbline = 0, .file = NULL, .line = NULL, .ret_cmd = 0,
			.ret_sh = 1, .blt_fct = builtin_fct,
			.cmds = NULL, .env = &env_lst};
	if (ac != 1)
	{
		sh.file = av[1];
		sh.fd = open(av[1], O_RDONLY);
		ft_infile(&sh);
	}
	else
		ft_prompt(&sh);
	if (fd != STDIN_FILENO && close(fd) < 0
		&& ft_dprintf(2, "Close of fd in main not ok\n"))
		return (1);
	return (sh.ret_sh);
}

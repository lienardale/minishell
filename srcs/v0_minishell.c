/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v0_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 13:06:27 by alienard          #+#    #+#             */
/*   Updated: 2020/07/22 12:47:56 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

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
			.fd = fd, .line = NULL, .ret_cmd = 1,
			.ret_sh = 1, .blt_fct = builtin_fct,
			.cmds = NULL, .env = &env_lst};
	if (ac != 1)
	{
		sh.fd = open(av[1], O_RDONLY);
		ft_infile(&sh);
	}
	else 
		ft_prompt(&sh);
	// temp = env_lst;
	// while (temp)
	// {
	// 	printf("%s=%s\n", ((t_env*)temp->content)->key, ((t_env*)temp->content)->value);
	// 	temp = temp->next;
	// }
	// ft_free_split(env);
	// ft_lstclear(&env_lst, ft_free_env_lst);
	if (close(fd) < 0)
	{
		ft_dprintf(2, "Close of fd in main not ok\n");
		return (1);
	}
	return (sh.ret_sh);
}

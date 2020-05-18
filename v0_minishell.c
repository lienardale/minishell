/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v0_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 13:06:27 by alienard          #+#    #+#             */
/*   Updated: 2020/05/18 17:50:49 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

int	main(int ac, char **av, char **env)
{
	int					check;
	int					i;
	// t_sh	sh;

	if (ac != 1)
		return EXIT_FAILURE;
	(void)av;
	if (!(env = ft_start_minishell(env)))
		return (EXIT_FAILURE);
for (i = 0; env[i] != NULL; i++)
ft_printf("%s\n", env[i]);
	ft_prompt(&check, 0, env);
	// system("leaks minishell");
//ft_free_split(env);
	return (check == 0) ? EXIT_FAILURE : EXIT_SUCCESS;
}

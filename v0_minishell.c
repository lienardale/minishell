/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v0_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 13:06:27 by alienard          #+#    #+#             */
/*   Updated: 2020/05/15 20:55:05 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

int	main(int ac, char **av, char **env)
{
	int		check;
	// int		i;
	// t_sh	sh;

	if (ac != 1)
		return EXIT_FAILURE;
	(void)av;
	// for (i = 0; env[i] != NULL; i++)
	// 	ft_printf("%s\n", env[i]);
	ft_prompt(&check, 0, env);
	system("leaks minishell");
	return (check == 0) ? EXIT_FAILURE : EXIT_SUCCESS;
}

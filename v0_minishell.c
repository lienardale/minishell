/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v0_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 13:06:27 by alienard          #+#    #+#             */
/*   Updated: 2020/06/11 16:21:31 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

int	main(int ac, char **av, char **env)
{
	int					check;
//int					i;
	// t_sh	sh;
	t_list				*env_lst;
//t_list				*temp;

	if (ac != 1)
		return EXIT_FAILURE;
	(void)av;
	env_lst = NULL;
	check = 0;
	if (!(env_lst = ft_start_minishell(env)))
		return (EXIT_FAILURE);
/*
temp = env_lst;
while (temp)
{
printf("%s=%s\n", ((t_env*)temp->content)->key, ((t_env*)temp->content)->value);
temp = temp->next;
}
(void)check;
*/
//for (i = 0; env[i] != NULL; i++)
//ft_printf("%s\n", env[i]);
//	ft_prompt(&check, 0, env);
	ft_prompt(&check, 0, &env_lst);
//	system("leaks minishell");
//ft_free_split(env);
//	ft_lstclear(&env_lst, ft_free_env_lst);
	return (check == 0) ? EXIT_FAILURE : EXIT_SUCCESS;
}

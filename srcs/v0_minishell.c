/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v0_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 13:06:27 by alienard          #+#    #+#             */
/*   Updated: 2020/06/25 16:17:30 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

int	main(int ac, char **av, char **env)
{
	int		check;
	// int		i;
	// t_sh	sh;
	t_list	*env_lst;
	int		fd;
	//t_list	*temp;

	// if (ac != 1)
		// return (EXIT_FAILURE);
	env_lst = NULL;
	check = 0;
	fd = 0;
	if (!(env_lst = ft_start_minishell(env)))
		return (EXIT_FAILURE);
	if (ac != 1)
	{
		fd = open(av[1], O_RDONLY);
		ft_infile(&check, fd, &env_lst);
	}
	else 
		ft_prompt(&check, fd, &env_lst);
	// ft_print_double_array(env, "env0");

	// temp = env_lst;
	// while (temp)
	// {
	// 	printf("%s=%s\n", ((t_env*)temp->content)->key, ((t_env*)temp->content)->value);
	// 	temp = temp->next;
	// }
	// (void)check;

	// for (i = 0; env[i] != NULL; i++)
	// 	ft_printf("%s\n", env[i]);
	// ft_prompt(&check, 0, env);
	
	// system("leaks minishell");
	// ft_free_split(env);
	// ft_lstclear(&env_lst, ft_free_env_lst);
	if (close(fd) < 0)
	{
		ft_dprintf(2, "close not ok\n");
		return (1);
	}
	return (check == 0) ? EXIT_FAILURE : EXIT_SUCCESS;
}

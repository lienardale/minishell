/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 18:44:40 by cdai              #+#    #+#             */
/*   Updated: 2020/09/11 14:07:25 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_cmd *cmd, t_sh *sh)
{
	char	*cwd;
	int		buff_size;
	t_list	*env;

	// (void)sh;
	(void)cmd;
	env = *sh->env;
	buff_size = 1000;
// mettre PWD=''
	if (!(cwd = ft_calloc(1, buff_size)))
		return (0);
	if (!(getcwd(cwd, buff_size)))
	{
		env = ft_search_env(env, "PWD");
		if (env && env->content && ((t_env*)(env->content))->value)
			cwd = ((t_env*)(env->content))->value;
	}
	ft_printf("%s\n", cwd);
	free(cwd);
	// ft_free_split(cmd->av);
	return (0);
}

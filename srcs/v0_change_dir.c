/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v0_change_dir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdai <cdai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 17:10:39 by cdai              #+#    #+#             */
/*   Updated: 2020/08/03 15:27:12 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

static t_list	*ft_change_dir_update(t_list **env, char *oldpwd)
{
	t_env	*oldpwd_env;
	t_env	*pwd_env;
	char	*pwd;

	if (!(pwd = ft_getcwd()))
		return (NULL);
	if (!(oldpwd_env = ft_new_env_var("OLDPWD", oldpwd)))
		return (NULL);
	else if (!(ft_update_env(*env, oldpwd_env)))
		return (NULL);
	if (!(pwd_env = ft_new_env_var("PWD", pwd)))
		return (NULL);
	else if (!(ft_update_env(*env, pwd_env)))
		return (NULL);
	free(pwd);
	return (*env);
}

int	ft_change_dir(char **args, t_list **env)
{
	int		chdir_value;
	t_list	*home;
	char	*oldpwd;

	chdir_value = -1;
	if (!(oldpwd = ft_getcwd()))
		return (1);
// faire . et .. ?
	if (!args[1] || (!ft_strcmp(args[1], "~") && !args[2]))
	{
		if (!(home = ft_search_env(*env, "HOME")))
		{
			ft_printf("minishell: cd: HOME not set\n");
ft_free_split(args);
			return (1);
		}
// if (home)
		chdir_value = chdir(((t_env*)home->content)->value);
	}
	else if (args[1] && args[2])
		chdir_value = -2;
	else
		chdir_value = chdir(args[1]);
//	(void)env;
// change pwd et oldpwd dans env
	if (chdir_value == -2)
	{
		ft_putstr_fd("Too much arguments\n", 0);
ft_free_split(args);
		return (1);
	}
	else if (chdir_value)
	{
		ft_putstr_fd("No such file or directory: ", 0);
		ft_putstr_fd(args[1], 0);
		ft_putchar_fd('\n', 0);
ft_free_split(args);
		return (1);
	}
	if (!ft_change_dir_update(env, oldpwd))
	{
ft_free_split(args);
		return (1);
	}
	free(oldpwd);
ft_free_split(args);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v0_change_dir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 17:10:39 by cdai              #+#    #+#             */
/*   Updated: 2020/08/05 14:10:43 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

static t_list	*ft_change_dir_update(t_list **env, char *oldpwd)
{
	t_env	*oldpwd_env;
	t_env	*pwd_env;
	char	*pwd;

	pwd = ft_calloc(1, 1000);
	getcwd(pwd, 1000);
	if (!(oldpwd_env_lst = ft_new_env_var("OLDPWD", oldpwd)))
		return (NULL);
	else if (!(ft_update_env(*env, oldpwd_env)))
		return (NULL);
	if (!(pwd_env_lst = ft_new_env_var("PWD", pwd)))
		return (NULL);
	else if (!(ft_update_env(*env, pwd_env)))
		return (NULL);
	free(pwd);
	return (*env);
}

int	ft_change_dir(t_cmd *cmd, t_sh *sh)
{
	int		chdir_value;
	t_list	*home;
	char	*oldpwd;

	chdir_value = -1;
oldpwd = ft_calloc(1, 1000);
getcwd(oldpwd, 1000);
// faire . et .. ?
	if (!cmd->av[1] || (!ft_strcmp(cmd->av[1], "~") && !cmd->av[2]))
	{
		if (!(home = ft_search_env(*(sh->env), "HOME")))
		{
			ft_printf("minishell: cd: HOME not set\n");
ft_free_split(cmd->av);
			return (1);
		}
// if (home)
		chdir_value = chdir(((t_env*)home->content)->value);
	}
	else if (cmd->av[1] && cmd->av[2])
		chdir_value = -2;
	else
		chdir_value = chdir(cmd->av[1]);
//	(void)env;
// change pwd et oldpwd dans env
	if (chdir_value == -2)
	{
		ft_putstr_fd("Too much arguments\n", 0);
		ft_free_split(cmd->av);
		return (1);
	}
	else if (chdir_value)
	{
		ft_putstr_fd("No such file or directory: ", 0);
		ft_putstr_fd(cmd->av[1], 0);
		ft_putchar_fd('\n', 0);
		ft_free_split(cmd->av);
		return (1);
	}
	ft_free_split(cmd->av);
	ft_change_dir_update(env, oldpwd);
	free(oldpwd);
	return (1);
}

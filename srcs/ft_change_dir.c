/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change_dir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 17:10:39 by cdai              #+#    #+#             */
/*   Updated: 2020/09/09 15:08:26 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*ft_change_dir_update(t_list **env, char *oldpwd)
{
	t_env	*oldpwd_env;
	t_env	*pwd_env;
	char	*pwd;

	pwd = NULL;
	oldpwd_env = NULL;
	pwd_env = NULL;
	pwd = ft_getcwd();
	// if (!(pwd = ft_getcwd()))
	// 	return (NULL);
	if (pwd)
		oldpwd_env = ft_new_env_var("OLDPWD", oldpwd);
	// if (!(oldpwd_env = ft_new_env_var("OLDPWD", oldpwd)))
	// 	return (NULL);
	if (oldpwd_env)
		ft_update_env(*env, oldpwd_env, false);
	// else if (!(ft_update_env(*env, oldpwd_env, false)))
	// 	return (NULL);
	if (pwd)
		pwd_env = ft_new_env_var("PWD", pwd);
	else
		pwd_env = ft_new_env_var("PWD", oldpwd);
	// if (!(pwd_env = ft_new_env_var("PWD", pwd)))
	// 	return (NULL);
	if (pwd_env)
		ft_update_env(*env, pwd_env, false);
	// else if (!(ft_update_env(*env, pwd_env, false)))
	// 	return (NULL);
	free(pwd);
	return (*env);
}

int	ft_change_dir(t_cmd *cmd, t_sh *sh)
{
	int		chdir_value;
	t_list	*home;
	char	*oldpwd;
	char	*newpwd;
	t_list	*env;

	chdir_value = -1;
	newpwd = NULL;
	env = (t_list*)(*sh->env);
	if (!(oldpwd = ft_getcwd()) && cmd->av[1])
	{
		env = ft_search_env(env, "PWD");
		if (env && env->content && ((t_env*)(env->content))->key)
		{
			if (ft_strcmp(cmd->av[1], ".") == 0)
				newpwd = ft_strjoin(((t_env*)(env->content))->value, "/.");
			else
				newpwd = ft_strdup(((t_env*)(env->content))->value);
		}
		if (ft_strcmp(cmd->av[1], "..") != 0 && ft_strcmp(cmd->av[1], "~") != 0)
		{
				ft_dprintf(2, "cd: error retrieving current directory:");
				ft_dprintf(2, " getcwd: cannot access parent directories:");
				ft_dprintf(2, " No such file or directory\n");
		}
		// printf("%s\n", newpwd);
		// return (1);
	}
// message error ?
// faire . et .. ? automatique
	if (!cmd->av[1] || (!ft_strcmp(cmd->av[1], "~") && !cmd->av[2]))
	{
		if (!(home = ft_search_env(*(sh->env), "HOME")))
		{
			ft_dprintf(2, "minishell: cd: HOME not set\n");
			ft_free_split(cmd->av);
			return (1);
		}
// if (home)
		chdir_value = chdir(((t_env*)home->content)->value);
	}
	else
		chdir_value = chdir(cmd->av[1]);
//	(void)env;
// change pwd et oldpwd dans env
	if (chdir_value && oldpwd)
	{
		if (sh->nbline)
			ft_dprintf(2, "%s: line %d: cd: %s: No such file or directory\n", sh->file, sh->nbline, cmd->av[1]);
		else
			ft_dprintf(2, "minishell: cd: %s: No such file or directory\n", cmd->av[1]);
		ft_free_split(cmd->av);
		return (1);
	}
	if (oldpwd && !ft_change_dir_update(sh->env, oldpwd))
	{
		if (sh->nbline)
			ft_dprintf(2, "%s: line %d: cd: %s: No such file or directory\n", sh->file, sh->nbline, cmd->av[1]);
		else
			ft_dprintf(2, "minishell: cd: %s: No such file or directory\n", cmd->av[1]);
		ft_free_split(cmd->av);
		return (1);
	}
	if (newpwd && !ft_change_dir_update(sh->env, newpwd))
		return (1);
	if (oldpwd)
		free(oldpwd);
	if (newpwd)
		free(newpwd);
	ft_free_split(cmd->av);
	return (0);
}

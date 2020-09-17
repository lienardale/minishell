/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change_dir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 17:10:39 by cdai              #+#    #+#             */
/*   Updated: 2020/09/17 13:52:07 by alienard         ###   ########.fr       */
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
	if (pwd)
		oldpwd_env = ft_new_env_var("OLDPWD", oldpwd);
	if (oldpwd_env)
		ft_update_env(*env, oldpwd_env, false);
	if (pwd)
		pwd_env = ft_new_env_var("PWD", pwd);
	else
		pwd_env = ft_new_env_var("PWD", oldpwd);
	if (pwd_env)
		ft_update_env(*env, pwd_env, false);
	free(pwd);
	return (*env);
}

static void		ft_nogetcwd(t_list **env, char **newpwd, t_cmd *cmd)
{
	*env = ft_search_env(*env, "PWD");
	if (*env && (*env)->content && ((t_env*)((*env)->content))->key)
	{
		if (ft_strcmp(cmd->av[1], ".") == 0)
			*newpwd = ft_strjoin(((t_env*)((*env)->content))->value, "/.");
		else
			*newpwd = ft_strdup(((t_env*)((*env)->content))->value);
	}
	if (ft_strcmp(cmd->av[1], "..") != 0 && ft_strcmp(cmd->av[1], "~") != 0)
	{
		ft_dprintf(2, "cd: error retrieving current directory:");
		ft_dprintf(2, " getcwd: cannot access parent directories:");
		ft_dprintf(2, " No such file or directory\n");
	}
}

static int		ft_chdir(int chdir_value, char *oldpwd, t_cmd *cmd, t_sh *sh)
{
	if (chdir_value && oldpwd)
		return (ft_strerror(cmd, sh, "No such file or directory"));
	if (oldpwd && !ft_change_dir_update(sh->env, oldpwd))
		return (ft_strerror(cmd, sh, "No such file or directory"));
	return (0);
}

int				ft_change_dir(t_cmd *cmd, t_sh *sh)
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
		ft_nogetcwd(&env, &newpwd, cmd);
	if (!cmd->av[1] || (!ft_strcmp(cmd->av[1], "~") && !cmd->av[2]))
	{
		if (!(home = ft_search_env(*(sh->env), "HOME")))
			return (ft_strerror(cmd, sh, "HOME not set"));
		chdir_value = chdir(((t_env*)home->content)->value);
	}
	else
		chdir_value = chdir(cmd->av[1]);
	if (ft_chdir(chdir_value, oldpwd, cmd, sh)
		|| (newpwd && !ft_change_dir_update(sh->env, newpwd)))
		return (1);
	ft_safe_free((void**)&oldpwd);
	ft_safe_free((void**)&newpwd);
	return (0);
}

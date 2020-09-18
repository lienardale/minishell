/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 18:50:38 by alienard          #+#    #+#             */
/*   Updated: 2020/09/18 10:52:23 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_strerror(t_cmd *cmd, t_sh *sh, char *str)
{
	if (sh->nbline)
		ft_dprintf(2, "%s: line %d: %s: %s: %s\n",
		sh->file, sh->nbline, cmd->cmd, cmd->av[1], str);
	else
		ft_dprintf(2, "minishell: %s: %s: %s\n",
		cmd->cmd, cmd->av[1], str);
	return (1);
}

void	ft_exporterror(t_cmd *cmd, t_sh *sh, char *str, int i)
{
	if (sh->nbline)
		ft_dprintf(2,
		"%s: line %d: %s: `%s': %s\n",
		sh->file, sh->nbline, cmd->cmd, cmd->av[i], str);
	else
		ft_dprintf(2,
		"minishell: %s: `%s': %s\n",
		cmd->cmd, cmd->av[i], str);
}

void	ft_redirerror(t_sh *sh, char *tmp, char *str)
{
	sh->nbline ? ft_dprintf(2,
			"%s: line %d: %s: %s\n",
			sh->file, sh->nbline, tmp, str)
			: ft_dprintf(2,
			"minishell: %s: %s\n", tmp, str);
}

void	ft_redir_indir_error(t_sh *sh, char *tmp, DIR **dir)
{
	if ((*dir = opendir(tmp)) && sh->nbline)
		ft_dprintf(2, "%s: line %d: %s: Is a directory\n",
			sh->file, sh->nbline, tmp);
	else if ((*dir = opendir(tmp)))
		ft_dprintf(2, "minishell: %s: Is a directory\n", tmp);
	else if (sh->nbline)
		ft_dprintf(2, "%s: line %d: %s: No such file or directory\n",
			sh->file, sh->nbline, tmp);
	else
		ft_dprintf(2, "minishell: %s: No such file or directory\n", tmp);
	ft_safe_free((void**)dir);
	ft_safe_free((void**)&tmp);
}

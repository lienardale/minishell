/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_debug.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 15:09:36 by alienard          #+#    #+#             */
/*   Updated: 2020/10/28 16:49:53 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_print_cmds(t_sh *sh)
{
    t_dlist     *cmd;
    t_cmd       *tmp;
    int         i;

    cmd = sh->cmds->head;
    i = 0;
    while (cmd && cmd->data)
    {
        tmp = (t_cmd*)(cmd->data);
        ft_printf("\n -- CMD %d -- \n", i);
        ft_printf("cmd->ac:|%d|\n", tmp->ac);
        tmp->av ? ft_print_double_array(tmp->av,"cmd->av") : 0;
        ft_printf("cmd->after:|%d|\n", tmp->after);
        ft_printf("cmd->before:|%d|\n", tmp->before);
        ft_printf("cmd->redir:|%s|\n", tmp->file_redir);
        cmd = cmd->next;
        i++;
    }
    
}

void    ft_print_sh(t_sh *sh)
{
    ft_printf("sh->fd:%d\n", sh->fd);
    ft_printf("sh->file:%s\n", sh->file);
    ft_printf("sh->line:%s\n", sh->line);
    ft_printf("sh->ret_cmd:%d\n", sh->ret_cmd);
    ft_printf("sh->ret_sh:%d\n", sh->ret_sh);
}

void    ft_print_all(t_sh *sh)
{
    ft_print_sh(sh);
    ft_print_cmds(sh);
}

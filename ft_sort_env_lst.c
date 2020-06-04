/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_env_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdai <cdai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 14:13:53 by cdai              #+#    #+#             */
/*   Updated: 2020/06/04 18:12:03 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

void	ft_sort_env_lst(t_list *env_lst)
{
	t_list	*previous;
	t_list	*lst_temp;

	lst_temp = env_lst;
	while (lst_temp)
	{
		previous = lst_temp->next;
		if (previous && ft_strcmp(((t_env*)previous->content)->key, ((t_env*)lst_temp->content)->key) > 0)
		{
			ft_swap_addr((void **)&(previous->content), (void **)&(lst_temp->content));
			lst_temp = env_lst;
		}
		else
			lst_temp = lst_temp->next;
	}
}

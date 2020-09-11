/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_env_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/31 15:38:40 by cdai              #+#    #+#             */
/*   Updated: 2020/09/11 13:59:14 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_env_lst(void *env_lst)
{
	t_env	*temp;

	if (!env_lst)
		return ;
	temp = (t_env*)env_lst;
	if (temp->key)
		free(temp->key);
	if (temp->value)
		free(temp->value);
	free(temp);
}

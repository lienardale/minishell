/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_env_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/31 15:38:40 by cdai              #+#    #+#             */
/*   Updated: 2020/07/20 12:02:11 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

void	ft_free_env_lst(void *env_lst)
{
	t_env	*temp;

	temp = env_lst;
	if (temp->key)
		free(temp->key);
	if (temp->value)
		free(temp->value);
	free(temp);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_env_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard@student.42.fr <alienard>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/31 15:38:40 by cdai              #+#    #+#             */
/*   Updated: 2020/09/10 18:37:56 by alienard@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_env_lst(void *env_lst)
{
	t_env	*temp;

	temp = (t_env*)env_lst;
	if (temp->key)
		free(temp->key);
	if (temp->value)
		free(temp->value);
	free(temp);
}

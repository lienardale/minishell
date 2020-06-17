/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 14:12:37 by alienard          #+#    #+#             */
/*   Updated: 2020/06/17 16:48:47 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

void	ft_print_dlst(t_dlist *node)
{
	while (node)
	{
		ft_printf("%p\n", node->data);
		node = node->next;
	}
}

size_t	ft_len_dlst(t_dlist **begin)
{
	t_dlist	*tmp;
	size_t	len;

	len = 0;
	tmp = *begin;
	while (tmp)
	{
		tmp = tmp->next;
		len++;
	}
	return (len);
}

t_dlist	*ft_dlst_new_node(void *data)
{
	t_dlist *new;

	if (!(new = ft_calloc(1, sizeof(t_dlist))))
		return (NULL);
	new->data = data;
	return (new);
}

void	ft_dlst_goto_end(t_dlist **last)
{
	while ((*last)->next)
		*last = (*last)->next;
}

void	ft_dslt_addfront(t_dlist **begin, void *data)
{
	t_dlist	*new;

	if (!(new = ft_dlst_new_node(data)))
		return (NULL);
	new->next = (*begin);
	new->prev = NULL;
	if ((*begin))
		(*begin)->prev = new;
	(*begin) = new;
}

void	ft_dlst_addback(t_dlist **begin, void *data)
{
	t_dlist	*new;
	t_dlist	*last;

	last = *begin;
	if (!(new = ft_dlst_new_node(data)))
		return (NULL);
	new->next = NULL;
	if (!begin)
	{
		new->prev = NULL;
		return ;
	}
	ft_dlst_goto_end(&last);
	last->next = new;
	new->prev = last;
}

void	ft_dlst_addafter(t_dlist *prev, void *data)
{
	t_dlist	*new;

	if (!prev)
		return (NULL);
	if (!(new = ft_dlst_new_node(data)))
		return (NULL);
	new->next = prev->next;
	prev->next = new;
	new->prev = prev;
	if (new->next)
		new->next->prev = new;
}

void	ft_dlst_addbefore(t_dlist **begin, t_dlist *next, void *data)
{
	t_dlist	*new;

	if (!next)
		return (NULL);
	if (!(new = ft_dlst_new_node(data)))
		return (NULL);
	new->prev = next->prev;
	next->prev = new;
	new->next = next;
	if (new->prev)
		new->prev->next = new;
	else
		(*begin) = new;
}

void	ft_dlst_delone(t_dlist **begin, t_dlist *del)
{
	if (*begin == NULL || !del)
		return ;
	if (*begin = del)
		*begin = del->next;
	if (del->next)
		del->next->prev = del->prev;
	if (del->prev)
		del->prev->next = del->next;
	free(del);
}

void	ft_dlst_reverse(t_dlist **begin)
{
	t_dlist	*tmp;
	t_dlist	*current;

	tmp = NULL;
	current = *begin;
	while (current)
	{
		tmp = current->prev;
		current->prev = current->next;
		current->next = tmp;
		current = current->prev;
		if (tmp)
			*begin = tmp->prev;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 14:12:37 by alienard          #+#    #+#             */
/*   Updated: 2020/06/18 14:52:28 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

void	ft_init_dlst(t_ref **dlst)
{
	if (!((*dlst) = ft_calloc(1, sizeof(t_ref))))
		return (NULL);
	(*dlst)->head = NULL;
	(*dlst)->tail = NULL;
	(*dlst)->size = 0;
}

void	ft_print_dlst(t_dlist *dlst, char *str)
{
	int i;

	i = 0;
	ft_printf("--- %d nodes ---\n", ft_len_dlst(dlst));
	if (str)
		ft_printf("| %s\n", str);
	while (dlst)
	{
		ft_printf("| %d | \"%s\" (p='%s'|n='%s')\n",
			i++, dlst->data,
			dlst->prev ? dlst->prev->data : "",
			dlst->next ? dlst->next->data : "");
		dlst = dlst->next;
	}
	ft_printf("---------------\n\n");
}

size_t	ft_len_dlst(t_dlist *dlst)
{
	size_t	len;

	len = 0;
	while (dlst)
	{
		dlst = dlst->next;
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

void	ft_dslt_addfront(t_ref *ref, void *data)
{
	t_dlist	*new;

	if (!(new = ft_dlst_new_node(data)))
		return (NULL);
	new->next = ref->head;
	new->prev = NULL;
	if (ref->head)
		ref->head->prev = new;
	ref->head = new;
}

void	ft_dlst_addback(t_ref *ref, void *data)
{
	t_dlist	*new;

	if (!(new = ft_dlst_new_node(data)))
		return (NULL);
	new->next = NULL;
	if (!ref->head)
	{
		new->prev = NULL;
		return ;
	}
	ref->tail->next = new;
	new->prev = ref->tail;
	ref->tail = new;
}

void	ft_dlst_addafter(t_ref *dlst, t_dlist *prev, void *data)
{
	t_dlist	*new;
	t_dlist	*tmp;

	if (!prev)
		return (NULL);
	if (!(new = ft_dlst_new_node(data)))
		return (NULL);
	new->next = prev->next;
	prev->next = new;
	new->prev = prev;
	if (new->next)
		new->next->prev = new;
	else
		dlst->tail = new;
	
}

void	ft_dlst_addbefore(t_ref *dlst, t_dlist *next, void *data)
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
		dlst->head = new;
}

void	ft_dlst_delone(t_ref *dlst, t_dlist *del)
{
	if (dlst->head == NULL || !del)
		return ;
	if (dlst->head = del)
		dlst->head = del->next;
	if (del->next)
		del->next->prev = del->prev;
	if (del->prev)
		del->prev->next = del->next;
	if (del->data)
	{
		free(del->data);
		del->data = NULL;
	}
	free(del);
	del = NULL;
}

void	ft_dlst_del(t_ref *dlst)
{
	t_dlist	*tmp;
	t_dlist	*tmp2;

	if (!dlst || !dlst->head)
		return ;
	tmp = dlst->head;
	tmp2 = dlst->head;
	while (tmp)
	{
		tmp2 = tmp2->next;
		ft_dlst_delone(dlst, tmp);
		tmp = tmp2;
	}
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 14:04:38 by alienard          #+#    #+#             */
/*   Updated: 2020/06/19 15:39:28 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

typedef struct		s_dlist
{
	void			*data;
	struct s_dlist	*prev;
	struct s_dlist	*next;
}					t_dlist;

typedef struct	s_ref
{
	t_dlist		*head;
	t_dlist		*tail;
	size_t		size;
}				t_ref;

void			ft_print_dlst(t_dlist *dlst, char *str);
size_t			ft_len_dlst(t_dlist *dlst);
t_dlist			*ft_dlst_new_node(void *data);
void			ft_dlst_goto_end(t_dlist **last);
void			ft_dslt_addfront(t_ref *ref, void *data);
void			ft_dlst_addback(t_ref *ref, void *data);
void			ft_dlst_addafter(t_ref *dlst, t_dlist *prev, void *data);
void			ft_dlst_addbefore(t_ref *dlst, t_dlist *next, void *data);
void			ft_dlst_delone(t_ref *dlst, t_dlist *del);
void			ft_dlst_del(t_ref *dlst);
void			ft_dlst_reverse(t_dlist **begin);
void			ft_init_dlst(t_ref **dlst);

# endif
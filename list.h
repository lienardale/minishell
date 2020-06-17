/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 14:04:38 by alienard          #+#    #+#             */
/*   Updated: 2020/06/17 16:32:26 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

typedef struct	s_dlist
{
	void	*data;
	struct s_dlist *prev;
	struct s_dlist *next;
}				t_dlist;

void			ft_print_dlst(t_dlist *node);
size_t			ft_len_dlst(t_dlist **begin);
t_dlist			*ft_dlst_new_node(void *data);
void			ft_dlst_goto_end(t_dlist **last);
void			ft_dslt_addfront(t_dlist **begin, void *data);
void			ft_dlst_addback(t_dlist **begin, void *data);
void			ft_dlst_addafter(t_dlist *prev, void *data);
void			ft_dlst_addbefore(t_dlist **begin, t_dlist *next, void *data);

# endif
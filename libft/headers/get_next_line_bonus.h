/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 12:11:38 by alienard          #+#    #+#             */
/*   Updated: 2020/09/16 17:14:35 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifdef BUFFER_SIZE
#  if BUFFER_SIZE < 0
#   undef BUFFER_SIZE
#   define BUFFER_SIZE 0
#  endif
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 200
# endif

# include <unistd.h>
# include <stdlib.h>

typedef struct	s_gnl
{
	int				currfd;
	int				ret;
	char			*rest;
	struct s_gnl	*next;
}				t_gnl;

typedef struct	s_buff
{
	char			buffer[BUFFER_SIZE];
	char			*tmp;
}				t_buff;

int				get_next_line_multi(int fd, char **line);
int				ft_check_ln(char **line, t_gnl *current, char *buffer);
int				ft_ifnl(char **line, t_gnl *current, size_t i, char *tmp);
char			*ft_strdup_buff(char *buffer, int ret);
size_t			ft_strlen_gnl(const char *str);
char			*ft_strdup_free_gnl(char *s1);
char			*ft_strjoin_free_gnl(char *s1, char *s2);
int				ft_error(char **line);

#endif

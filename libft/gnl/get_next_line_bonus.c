/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 12:11:22 by alienard          #+#    #+#             */
/*   Updated: 2020/09/11 12:36:13 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	ft_free_fd(t_gnl *current, t_gnl **begin)
{
	t_gnl	*tmp;
	t_gnl	*prev;
	t_gnl	*foll;

	prev = *begin;
	tmp = *begin;
	while (tmp && tmp->next && tmp->currfd != current->currfd)
	{
		tmp = tmp->next;
		if (prev->next && prev != tmp
			&& prev->next->currfd != current->currfd)
			prev = prev->next;
	}
	if (tmp == *begin)
	{
		*begin = tmp->next;
		free(current);
		return ;
	}
	foll = tmp->next;
	prev->next = foll;
	free(current);
}

void	ft_find_fd(int fd, t_gnl **begin, t_gnl **current)
{
	if (!(*begin))
	{
		if (!((*begin) = (t_gnl *)malloc(sizeof(t_gnl))))
			return ;
		(*begin)->rest = NULL;
		(*begin)->currfd = fd;
		(*begin)->ret = 0;
		(*begin)->next = NULL;
	}
	*current = *begin;
	while ((*current)->next && (*current)->currfd != fd)
		(*current) = (*current)->next;
	if ((*current)->currfd != fd)
	{
		if (!((*current)->next = (t_gnl *)malloc(sizeof(t_gnl))))
			return ;
		(*current)->next->rest = NULL;
		(*current)->next->currfd = fd;
		(*current)->next->ret = 0;
		(*current)->next->next = NULL;
		*current = (*current)->next;
	}
}

int		ft_ifnl(char **line, t_gnl *current, size_t i, char *tmp)
{
	char	*tmprest;
	size_t	j;
	size_t	len;

	j = -1;
	if (!(len = ft_strlen_gnl(current->rest))
		|| !(tmp = (char *)malloc(sizeof(char) * (i + 1))))
		return (-1);
	while (++j < i && current->rest[j])
		tmp[j] = current->rest[j];
	tmp[j] = '\0';
	current->rest[j] == '\n' ? j++ : 0;
	if (len < j)
		j = len;
	if ((len - j) == 0)
	{
		free(current->rest);
		current->rest = NULL;
		*line = tmp;
		return (1);
	}
	if (!(tmprest = (char *)malloc(sizeof(char) * (len - j + 1))))
		return (-1);
	i = 0;
	while (current->rest[j])
		tmprest[i++] = current->rest[j++];
	tmprest[i] = '\0';
	free(current->rest);
	current->rest = tmprest;
	*line = tmp;
	return (1);
}

int		ft_check_ln(char **line, t_gnl *current, char *buffer, t_gnl **begin)
{
	size_t	i;
	char	*tmp;

	i = -1;
	tmp = *line;
	if (!(current->rest = ft_strjoin_free_gnl(current->rest, buffer)))
		return (-1);
	while (current->rest[++i])
	{
		if (current->rest[i] == '\n')
		{
			if ((ft_ifnl(line, current, i, tmp)) == 1)
				return (1);
			return (-1);
		}
	}
	if (current->ret == 0)
	{
		*line = ft_strdup_free_gnl(current->rest);
		ft_free_fd(current, begin);
		return (0);
	}
	return (2);
}

int		get_next_line_multi(int fd, char **line)
{
	static t_gnl	*begin = NULL;
	t_gnl			*current;
	t_buff			buff;
	int				ret;

	if (fd <= -1 || !line || BUFFER_SIZE == 0)
		return (-1);
	ft_find_fd(fd, &begin, &current);
	// if (!begin)
	// 	*begin = (t_gnl){fd, 0, NULL, NULL};
	// current = begin
	while ((current->ret = read(fd, buff.buffer, BUFFER_SIZE)) > 0)
	{
		if (!(buff.tmp = ft_strdup_buff(buff.buffer, current->ret)))
			return (ft_error(line));
		if ((ret = ft_check_ln(line, current, buff.tmp, &begin)) == 1)
			return (1);
		if (ret != 2)
			return (ret == -1 ? ft_error(line) : 0);
	}
	if (current->ret == -1)
		return (-1);
	if (!(buff.tmp = (char*)malloc(sizeof(char) * 1)))
		return (ft_error(line));
	buff.tmp[0] = '\0';
	if ((ret = ft_check_ln(line, current, buff.tmp, &begin)) == 1)
		return (1);
	return (ret == -1 ? ft_error(line) : 0);
}

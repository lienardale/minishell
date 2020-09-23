/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 12:11:22 by alienard          #+#    #+#             */
/*   Updated: 2020/09/23 10:37:56 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_gnl		g_gnl;

static int	ft_free_rest(char **line, t_gnl *current, char *tmp, char *new)
{
	free(current->rest);
	current->rest = new;
	*line = tmp;
	return (1);
}

int			ft_ifnl(char **line, t_gnl *current, size_t i, char *tmp)
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
		return (ft_free_rest(line, current, tmp, NULL));
	if (!(tmprest = (char *)malloc(sizeof(char) * (len - j + 1))))
		return (-1);
	i = 0;
	while (current->rest[j])
		tmprest[i++] = current->rest[j++];
	tmprest[i] = '\0';
	return (ft_free_rest(line, current, tmp, tmprest));
}

int			ft_check_ln(char **line, t_gnl *current, char *buffer)
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
		*current = (t_gnl) {0, 0, "\0", NULL, NULL, NULL};
		return (0);
	}
	return (2);
}

int			get_next_line_multi(int fd, char **line)
{
	int				ret;

	if (fd <= -1 || !line || BUFFER_SIZE == 0)
		return (-1);
	g_gnl.currfd = fd;
	while ((g_gnl.ret = read(fd, g_gnl.buffer, BUFFER_SIZE)) > 0)
	{
		if (!(g_gnl.tmp = ft_strdup_buff(g_gnl.buffer, g_gnl.ret)))
			return (ft_error(line));
		if ((ret = ft_check_ln(line, &g_gnl, g_gnl.tmp)) == 1)
			return (1);
		if (ret != 2)
			return (ret == -1 ? ft_error(line) : 0);
		g_sh.sig = true;
	}
	if (g_gnl.ret == -1)
		return (-1);
	if (!(g_gnl.tmp = (char*)malloc(sizeof(char) * 1)))
		return (ft_error(line));
	g_gnl.tmp[0] = '\0';
	if ((ret = ft_check_ln(line, &g_gnl, g_gnl.tmp)) == 1)
		return (1);
	return (ret == -1 ? ft_error(line) : 0);
}

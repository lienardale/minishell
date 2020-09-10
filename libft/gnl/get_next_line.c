/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdai <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 11:52:19 by cdai              #+#    #+#             */
/*   Updated: 2020/09/02 12:54:55 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_strcut(char **buffer)
{
	int		i;
	int		j;

	i = -1;
	j = -1;
	while ((*buffer)[++i])
	{
		if ((*buffer)[i] == '\n')
		{
			i++;
			if (!(*buffer)[i])
			{
				free(*buffer);
				*buffer = 0;
				return (1);
			}
			while ((*buffer)[i + (++j)])
				(*buffer)[j] = (*buffer)[i + j];
			(*buffer)[j] = 0;
			return (1);
		}
	}
	free(*buffer);
	*buffer = 0;
	return (2);
}

static char	*ft_strjoin_mix(char *buffer, char **line)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = 0;
	while ((*line)[i])
		i++;
	while (buffer[j] && buffer[j] != '\n')
		j++;
	if (!(temp = malloc(sizeof(*temp) * (i + j + 1))))
		return (0);
	j = -1;
	while ((*line)[++j])
		temp[j] = (*line)[j];
	j = 0;
	while (buffer[j] && buffer[j] != '\n')
	{
		temp[i + j] = buffer[j];
		j++;
	}
	temp[i + j] = 0;
	free(*line);
	return (temp);
}

static int	ft_error_free(char **buffer, char **temp)
{
	free(*buffer);
	free(*temp);
	return (-1);
}

static int	ft_create_temp(int fd, char **temp, char **buffer)
{
	int			size;

	if (fd < 0 || !(*buffer = malloc(sizeof(**buffer) * (BUFFER_SIZE + 1)))
		|| (size = read(fd, *buffer, BUFFER_SIZE)) < 0)
	{
		free(*temp);
		return (-1);
	}
	(*buffer)[size] = 0;
	if (size != BUFFER_SIZE)
	{
		if (!(*temp = ft_strjoin_mix(*buffer, temp)))
			return (ft_error_free(buffer, temp));
		size = ft_strcut(buffer);
		if (size == 2)
			return (0);
		else
			return (1);
	}
	return (2);
}

int			get_next_line(int fd, char **line)
{
	static char	*buffer;
	char		*temp;
	int			line_finished;

	if (fd < 0 || !line || BUFFER_SIZE < 1)
		return (-1);
	if (!ft_init(line, &temp))
		return (-1);
	line_finished = 2;
	while (line_finished == 2)
	{
		if (!buffer)
			line_finished = ft_create_temp(fd, &temp, &buffer);
		if (line_finished == 2)
		{
			if (!(temp = ft_strjoin_mix(buffer, &temp)))
				return (ft_error_free(&buffer, &temp));
			line_finished = ft_strcut(&buffer);
		}
	}
	free(*line);
	*line = temp;
	return (line_finished);
}

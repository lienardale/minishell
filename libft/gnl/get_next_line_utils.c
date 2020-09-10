/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdai <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 10:09:16 by cdai              #+#    #+#             */
/*   Updated: 2019/11/19 10:33:15 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_init(char **line, char **temp)
{
	if (!(*line = malloc(sizeof(**line))) ||
		!(*temp = malloc(sizeof(**temp))))
		return (0);
	**line = 0;
	**temp = 0;
	return (1);
}

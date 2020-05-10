/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v0_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 08:14:14 by alienard          #+#    #+#             */
/*   Updated: 2020/05/08 16:44:12 by Dai Cleme        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

void	ft_prompt(int *check, int fd, char **env)
{
	char	*line;
	char	**args;
	int		ret;
	int		i;

	ret = 1;
	while (ret && (write(1,">",1)) && (*check = get_next_line(fd, &line)) >= 0)
	{
		i = 0;
		args = ft_split_line(line);
		ft_free_ptr(line);
while (args[i])
{
printf("%s\n", args[i]);
i++;
}
i = 0;
		ret = ft_parse_line(args, env);
		while (args[i])
			ft_free_ptr(args[i++]);
		ft_free_ptr(args);
		if (*check == 0)
			break ;
	}
}

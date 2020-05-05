/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v0_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 08:14:14 by alienard          #+#    #+#             */
/*   Updated: 2020/05/05 14:34:22 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

void	ft_prompt(int *check, int fd, char **env)
{
	char	*line;
	char	**args;
	int		ret;
	int		i;
	static int	(*builtin_fct[])(char **) = {BUILTINS};

	ret = 1;
	while (ret && (write(1,">",1)) && (*check = get_next_line(fd, &line)) >= 0)
	{
		i = 0;
		args = ft_split_line(line);
		ft_free_ptr(line);
		ret = ft_parse_line(args, env, builtin_fct);
		while (args[i])
			ft_free_ptr(args[i++]);
		ft_free_ptr(args);
		if (*check == 0)
			break ;
	}
}

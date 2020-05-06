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
	// char **prompt;
	// booleen quote;


	// booleen = 0;
	//prompt = malloc(sizeof(*char)); // liste chainee ?
	ret = 1;
	while (ret && (write(1,">",1)) && (*check = get_next_line(fd, &line)) >= 0)
	{
		i = 0;
		// prompt[0] /*normalement c'est j*/ = line;
		// j++; ou maillon suivant ?
		// quote = ft_check_line(line, quote); //ternaire ?
		// if (!quote) {
		args = ft_split_line(line);
		ret = ft_parse_line(args, env, builtin_fct);
		// ft_free_prompt(prompt);
		// }
		ft_free_ptr(line);
		while (args[i])
			ft_free_ptr(args[i++]);
		ft_free_ptr(args);
		if (*check == 0)
			break ;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdai <cdai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 07:54:41 by cdai              #+#    #+#             */
/*   Updated: 2020/05/27 13:00:21 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

static int	ft_export_check_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		else if (!ft_isalpha(str[i]))
			return (-1);
		i++;
	}
	return (1);
}

static int	ft_export_chr(char **strs, char *arg)
{
	int		i;
	int		arg_len;

	i = 0;
	arg_len = ft_export_check_str(arg);
	while (strs[i])
	{
		if (ft_strncmp(strs[i], arg, arg_len) == 0)
		{
			if (ft_strcmp(strs[i] + arg_len + 1, arg + arg_len + 1) != 0)
			{
				free(strs[i]);
				strs[i] = ft_strdup(arg);
				
			}
			else 
				return (1);
		}
		i++;
	}
	return (0);
}

int	ft_export(char **args, char **env)
{
	int		i;
	int		j;
	int		export_chr_ret_value;
	char	**temp;

	i = 0;
	j = 0;
	export_chr_ret_value = 0;
	temp = 0;
	if (!args[1])
	{
		temp = ft_splitcpy(env);
		ft_strsort(temp);
		while (temp[i])
		{
			ft_putendl_fd(temp[i], 0);
			i++;
		}
		ft_free_split(temp);
	}
	else
	{
		i++;
		while (args[i])
		{
			if (ft_export_check_str(args[i]) == -1 || ft_export_check_str(args[i]) == 0)
				ft_putstr_fd("bad character\n", 0);
			else if (((export_chr_ret_value = ft_export_chr(env, args[i])) == -1))
			{
				ft_free_split(args);
				ft_putstr_fd("malloc fail in ft_export\n", 0);
				return (1);
			}
			else if (export_chr_ret_value < 1 && !(temp = ft_splitadd_back(env, args[i])))
			{
				ft_free_split(args);
				ft_putstr_fd("malloc fail in ft_export\n", 0);
				return (1);
			}
			if (temp)
			{
				ft_free_split(env);
				env = temp;
			}
			printf("ft_export => %s\n", args[i]);
			i++;
		}
	}
ft_free_split(args);
	return (1);
}

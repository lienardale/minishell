/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_test_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 16:11:10 by alienard          #+#    #+#             */
/*   Updated: 2020/07/20 17:48:09 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <sys/errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include "libft/headers/libft.h"
#include "libft/headers/libftprintf.h"
#include "libft/headers/libftdprintf.h"
#include "libft/headers/libftfprintf.h"
#include "libft/headers/get_next_line_bonus.h"
#include "libft/headers/list.h"

int	main(void)
{
	int pipefd[2];
	pid_t p1, p2;
	char 	*tmp = "> test_file1 > test_file2";
	char	*file;
	int		i;
	int		j;

	if (pipe(pipefd) < 0)
	{
		printf("\nPipe could not be initialized");
		return (1);
	}
	// i = 0;
	// while (file[i])
	// {
	// 	while (file[i] == '>' || ft_isspace(file[i]))
	// 		i++;
	// 	j = i;
	// 	while ()
	// 	{
	// 		/* code */
	// 	}
		
	// }
	
	p1 = fork();
	if (p1 < 0)
	{
		printf("\nCould not fork");
		return (1);
	}
	if (p1 == 0)
	{
		// Child 1 executing.. 
		// It only needs to write at the write end 
		close(pipefd[0]); 
		if ((pipefd[1] = open("test_file2", O_WRONLY | O_CREAT | O_TRUNC, 0777)) == -1)
		{
			ft_dprintf(2, "Error in open.");
			return (1);
		}
		dup2(pipefd[1], STDOUT_FILENO); 
		printf("\ntest\n\n");
		close(pipefd[1]);
	}
	else
	{
		// Parent executing 
		p2 = fork();

		if (p2 < 0)
		{
			printf("\nCould not fork");
			return (1);
		}

		// Child 2 executing..
		// It only needs to read at the read end
		if (p2 == 0)
		{
			close(pipefd[1]);
			if ((pipefd[0] = open("test_file1", O_WRONLY | O_CREAT | O_TRUNC, 0777)) == -1)
			{
				ft_dprintf(2, "Error in open.");
				return (1);
			}
			dup2(pipefd[0], STDOUT_FILENO);
			printf("\ntest\n\n");
			close(pipefd[0]);
		}
		else
		{
			// parent executing, waiting for two children 
			wait(NULL); 
			wait(NULL); 
		} 
	} 
	return (0);
}
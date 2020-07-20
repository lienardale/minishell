# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alienard <alienard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/09 18:51:33 by alienard          #+#    #+#              #
#    Updated: 2020/08/05 12:28:33 by cdai             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

SRCS_DIR	= srcs

_SRCS		= v0_minishell.c \
				v0_prompt.c \
				v0_split.c \
				ft_parse_line.c \
				ft_parse_redir.c \
				ft_split_quote.c \
				v0_parse.c \
				v0_process.c \
				v0_echo.c \
				v0_exit.c \
				v0_parse_path.c \
				v0_lststrjoin.c \
				v0_isolate_exec.c \
				v0_change_dir.c \
				ft_env.c \
				ft_pwd.c \
				ft_export.c \
				ft_start_minishell.c \
				ft_split_to_lst_env.c \
				ft_free_env_lst.c \
				ft_sort_env_lst.c \
				ft_separate_key_value.c \
				ft_lst_env_to_split.c \
				ft_lst_env_to_split_export.c \
				ft_lst_env_to_split_launch.c \
				ft_search_env.c \
				ft_unset.c \
				ft_quote.c \
				ft_escape.c \
				ft_strdup_clean.c \
				ft_exec_env_var.c \
				ft_parse_env_var.c

SRCS			= $(addprefix $(SRCS_DIR)/, $(_SRCS))
OBJS			= $(SRCS:.c=.o)


RM				= rm -f
AR				= ar rc

CC				= gcc
CLANG			= clang
HEADER			= -I ./headers $(LIB_INCL)
CFLAGS			= -Wall -Wextra -Werror -g $(HEADER)

LIB_LNK			= -L $(LIB_PATH) -lft
LIB_PATH		= ./libft
LIBFT_MAKE		= @$(MAKE) -C $(LIB_PATH) --no-print-directory
LIB_INCL		= -I $(LIB_PATH) -I $(LIB_PATH)/headers
LIB				= $(LIB_LNK)

OBJS			=	$(SRCS:.c=.o)

all:			libmake
				@$(MAKE) $(NAME) --no-print-directory

$(NAME):		$(OBJS)
				$(CLANG) $(CFLAGS) -o $(NAME) $(OBJS) $(LIB)

libmake:
				$(LIBFT_MAKE)

bonus:			all

norme:
				$(LIB_MAKE) norme
				norminette $(SRCS)

clean:
				$(RM) -r $(OBJS)
				$(LIBFT_MAKE) clean
fclean:
				$(RM) -r $(OBJS)
				$(RM) $(NAME)
				$(LIBFT_MAKE) fclean

re:				fclean all

#rule test

OBJS_TEST		= $(SRCS:.c=.o)

.c.o:
				$(CLANG) $(CFLAGS) -c $< $(HEADER) -o $(<:.c=.o)

libft_test:
				make test -C libft

test:			libft_test $(OBJS_TEST)
				$(CLANG) $(CFLAGS) -o $(NAME) $(OBJS_TEST) $(LIBPATH)*.a

#DOCKER CMDS

docker:
	if \
		docker exec -ti work bash; \
		then \
			true; \
	elif \
		docker run -d -ti --name work minishell_image; \
		then \
			echo 'docker run succeeded'; \
			docker exec -ti work bash; \
	elif \
		docker restart work; \
		then \
			echo 'docker run failed'; \
			echo 'docker restart worked'; \
			docker exec -ti work bash; \
	elif \
		docker build -t minishell_image . && \
		docker run -d -ti --name work minishell_image; \
		then \
			echo 'docker run failed'; \
			echo 'docker restart failed'; \
			echo 'docker build then run succeeded'; \
			docker exec -ti work bash; \
	else \
		echo 'Docker no installed'; \
	fi

kill:
	docker kill work

config_cdai:
	git config --global user.email "cdai@student.42.fr";
	git config --global user.name "Dai Clement";
	sed 's/marvin/cdai/' 42header/vim/stdheader.vim | sed 's/42.fr/student.42.fr/' > ~/.vim/plugin/stdheader.vim;

config_alienard:
	git config --global user.email "alienard@student.42.fr";
	git config --global user.name "Lienard Alexandre";
	sed 's/marvin/alienard/' 42header/vim/stdheader.vim | sed 's/42.fr/student.42.fr/' > ~/.vim/plugin/stdheader.vim;

cdai:
	clang test.c libft/libft.a -Ilibft;
	./a.out;

leak:
	valgrind --leak-check=full --show-leak-kinds=all ./minishell;

.PHONY:		re all clean fclean libft_test test build run exec kill config_cdai config_alienard leak

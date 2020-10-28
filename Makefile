# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alienard <alienard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/09 18:51:33 by alienard          #+#    #+#              #
#    Updated: 2020/10/28 15:09:20 by alienard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

SRCS_DIR	= srcs

_SRCS		= ft_minishell.c \
				ft_prompt.c \
				ft_infile.c \
				ft_split_input.c \
				ft_parse_line.c \
				ft_init_args.c \
				ft_parse_redir.c \
				ft_split_quote.c \
				ft_split_handle_quote.c \
				ft_iterate_in_line.c \
				ft_preprocess.c \
				ft_process.c \
				ft_process_child.c \
				ft_blt_process.c \
				ft_exec_redir.c \
				ft_echo.c \
				ft_exit.c \
				ft_parse_path.c \
				ft_lststrjoin.c \
				ft_isolate_exec.c \
				ft_change_dir.c \
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
				ft_isin_squotes.c \
				ft_isin_dquotes.c \
				ft_escape.c \
				ft_pipe.c \
				ft_strdup_clean.c \
				ft_clean_envvar.c \
				ft_exec_env_var.c \
				ft_isin_env.c \
				ft_parse_env_var.c \
				ft_new_env_var.c \
				ft_update_env.c \
				ft_getcwd.c \
				ft_signal.c \
				ft_reset_sh.c \
				ft_error.c \
				ft_free_minishell.c \
				ft_free_cmds.c \
				get_next_line_bonus.c \
				get_next_line_utils_bonus.c \
				ft_minishell_sigoff.c \
				ft_debug.c

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

ifeq (search,$(firstword $(MAKECMDGOALS)))
    RUN_ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
    $(eval $(RUN_ARGS):;@:)
endif

search:
	grep -n $(RUN_ARGS) srcs/*.c headers/*.h libft/*/*.c libft/*/*.h

.PHONY:		re all clean fclean libft_test test build run exec kill config_cdai config_alienard leak search

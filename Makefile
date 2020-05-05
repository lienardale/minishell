# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alienard <alienard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/09 18:51:33 by alienard          #+#    #+#              #
#    Updated: 2020/05/04 14:20:38 by alienard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 		minishell

SRCS =		v0_minishell.c \
			v0_prompt.c \
			v0_split.c \
			v0_parse.c \
			v0_process.c

OBJS = 		$(SRCS:.c=.o)

CC =		gcc

RM = 		rm -f

AR = 		ar rc

HEADER = 	./

CFLAGS =	-Wall -Wextra -Werror -g

LIBFT_MAKE = 	$(MAKE) -C $(LIBPATH)

LIBPATH =	./libft/

.c.o:		$(SRCS)
			$(CC) $(CFLAGS) -c $< -I $(HEADER) -o $(<:.c=.o)

all:		libft/libft.a $(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBPATH)*.a

libmake:
			$(LIBFT_MAKE)

libft/libft.a:
		make -C $(LIBPATH)


$(LIB):
		make -C libft re

bonus:

clean:
			$(RM) $(OBJS)
			$(LIBFT_MAKE) fclean

fclean:		clean
			$(RM) $(NAME)
			$(LIBFT_MAKE) fclean

re:			fclean all

CLANG =		clang

OBJS_TEST =	$(SRCS:.c=.o)

.c.o:
			$(CLANG) $(CFLAGS) -c $< -I $(HEADER) -o $(<:.c=.o)

libft_test:
		make test -C libft

test:		libft_test $(OBJS_TEST)
			$(CLANG) $(CFLAGS) -o $(NAME) $(OBJS_TEST) $(LIBPATH)*.a

#DOCKER CMDS

# If the first argument is "run"...
ifeq (run,$(firstword $(MAKECMDGOALS)))
  # use the rest as arguments for "run"
  RUN_ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
  # ...and turn them into do-nothing targets
  $(eval $(RUN_ARGS):;@:)
endif
# If the first argument is "exec"...
ifeq (exec,$(firstword $(MAKECMDGOALS)))
  # use the rest as arguments for "exec"
  RUN_ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
  # ...and turn them into do-nothing targets
  $(eval $(RUN_ARGS):;@:)
endif

run:
	docker run -d -ti $(RUN_ARGS)

exec:
	docker exec -ti $(RUN_ARGS) bash

git_config_cdai:
	git config --global user.email "cdai@student.42.fr";
	git config --global user.name "Dai Clément";

git_config_alienard:
	git config --global user.email "alienard@student.42.fr";
	git config --global user.name "Liènard Alexandre";

.PHONY:		re all clean fclean

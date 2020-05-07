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


#rule test

CLANG =		clang

OBJS_TEST =	$(SRCS:.c=.o)

.c.o:
			$(CLANG) $(CFLAGS) -c $< -I $(HEADER) -o $(<:.c=.o)

libft_test:
		make test -C libft

test:		libft_test $(OBJS_TEST)
			$(CLANG) $(CFLAGS) -o $(NAME) $(OBJS_TEST) $(LIBPATH)*.a

#DOCKER CMDS

# If the first argument is "config"...
ifeq (config,$(firstword $(MAKECMDGOALS)))
  # use the rest as arguments for "config"
  RUN_ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
  # ...and turn them into do-nothing targets
  $(eval $(RUN_ARGS):;@:)
endif

build:
	docker build -t minishell_image .

run:
	docker run -d -ti --name minishell_workspace minishell_image

exec:
	docker exec -ti minishell_workspace bash

config_cdai:
	git config --global user.email "cdai@student.42.fr";
	git config --global user.name "Dai Clément";
	sed 's/marvin/cdai/' 42header/vim/stdheader.vim >> ~/.vim/plugin/stdheader.vim;
# I could do
#	echo USER=cdai >> ~/.bashrc; 
#	echo MAIL=cdai@student.42.fr >> ~/.bashrc;
#	source ~/.bashrc;
# I found this solution after.

config_alienard:
	git config --global user.email "alienard@student.42.fr";
	git config --global user.name "Liènard Alexandre";
	sed 's/marvin/alienard/' 42header/vim/stdheader.vim >> ~/.vim/plugin/stdheader.vim;

.PHONY:		re all clean fclean

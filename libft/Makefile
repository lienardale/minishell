# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alienard <alienard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/09 18:51:33 by alienard          #+#    #+#              #
#    Updated: 2020/06/18 15:28:26 by alienard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 			libft.a

BILIST_DIR		= bilist
CONVERT_DIR		= convert
DPRINTF_DIR		= dprintf
FPRINTF_DIR		= fprintf
GNL_DIR			= gnl
IS_DIR			= is
LIST_DIR		= list
MEM_DIR			= mem
PRINT_DIR		= print
PRINTF_DIR		= printf
STR_DIR			= str

INCLUDES_DIR	= ./headers

_BILIST 		= bilist
_CONVERT		= convert
_DPRINTF		= dprintf
_FPRINTF		= fprintf
_GNL			= gnl
_IS				= is
_LIST			= list
_MEM			= mem
_PRINT			= print
_PRINTF			= printf
_STR			= str

BILIST 			= $(addprefix $(BILIST_DIR)/, $(_BILIST))
CONVERT			= $(addprefix $(CONVERT_DIR)/, $(_CONVERT))
DPRINTF			= $(addprefix $(DPRINTF_DIR)/, $(_DPRINTF))
FPRINTF			= $(addprefix $(FPRINTF_DIR)/, $(_FPRINTF))
GNL				= $(addprefix $(GNL_DIR)/, $(_GNL))
IS				= $(addprefix $(IS_DIR)/, $(_IS))
LIST			= $(addprefix $(LIST_DIR)/, $(_LIST))
MEM				= $(addprefix $(MEM_DIR)/, $(_MEM))
PRINT			= $(addprefix $(PRINT_DIR)/, $(_PRINT))
PRINTF			= $(addprefix $(PRINTF_DIR)/, $(_PRINTF))
STR				= $(addprefix $(STR_DIR)/, $(_STR))

SRCS 			= $(BILIST) $(CONVERT) $(DPRINTF) $(FPRINTF) $(GNL) $(IS) $(LIST) $(MEM) $(PRINT) $(PRINTF) $(STR)
OBJS			= $(SRCS:.c=.o)
OBJS_TEST 		= $(SRCS:.c=.o)

CFLAGS			= -Wall -Wextra -Werror -g
CC				= gcc
CLANG			= clang

RM				= rm -f
AR				= ar rc
HEADER			= ./

# .c.o:		$(SRCS)
			# $(CC) $(CFLAGS) -c $< -I $(INCLUDES_DIR) -o $(<:.c=.o)

.c.o:			$(SRCS)
				$(CLANG) $(CFLAGS) -c $< -I $(INCLUDES_DIR) -o $(<:.c=.o)

all:			$(NAME)

$(NAME):		$(OBJS) headers/libft.h
				$(AR) $(NAME) $(OBJS)

clean:
				$(RM) $(OBJS) $(OBJSBONUS)

fclean:			clean
				$(RM) $(NAME)

norme:
				norminette $(SRCS) headers/libft.h

re:				fclean all

test:			$(OBJS_TEST)
				$(AR) $(NAME) $(OBJS)

.PHONY:			re all clean fclean

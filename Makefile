# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/08 10:32:48 by bcosters          #+#    #+#              #
#    Updated: 2021/09/20 11:24:33 by bcosters         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# -*- MakeFile for Simple debugs Library -*-

# -*- Variable definitions -*-

#	Project sources/objects/headers

SRCS	= ${wildcard *.c} 
OBJS	= ${SRCS:%.c=obj/%.o}
OBJDR	= obj/
HEADER	= malloc_leak_checker.h
NAME	= libmlc.a
CC		= gcc
CFLAGS 	= -Wall -Wextra -Werror

# -*- Rules -*-
#target: dependencies
#	action

#	Implicit rules

obj/%.o : %.c
			@$(CC) -c $(CFLAGS) $< -o $@
			@printf "#"

#	Normal rules

all:		$(NAME)

$(NAME):	$(OBJDR) $(OBJS) $(HEADER)
			@ar rcs $(NAME) $(OBJS)
			@printf "]\n"
			@echo
			@echo "Add the following flags to link the library:"
			@echo "-lmlc -L /PathToThisRepo/"

$(OBJDR):
			@echo "Compiling library..."
			@mkdir -p $(OBJDR)
			@printf "["

.PHONY:		clean

clean:
			@rm -rf ${OBJDR}

fclean:		clean
			@rm -f ${NAME}

re:			fclean all
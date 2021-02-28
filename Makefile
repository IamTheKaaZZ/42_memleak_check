# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bcosters <bcosters@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/08 10:32:48 by bcosters          #+#    #+#              #
#    Updated: 2021/02/28 14:10:28 by bcosters         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# -*- MakeFile for Simple debugs Library -*-

# -*- Variable definitions -*-

#	Project sources/objects/headers

SRCS	= malloc_leak_checker.c simple_debugs.c

OBJS	= ${SRCS:.c=.o}

HEADER	= simple_debugs.h

NAME	= debugs.a

CC		= gcc

CFLAGS 	= -Wall -Wextra -Werror

# -*- Rules -*-
#target: dependencies
#	action

#	Implicit rules

%.o : %.c
			$(CC) -c $(CFLAGS) $< -o $@

#	Normal rules

all:		$(NAME)

$(NAME):	$(OBJS) $(HEADER)
			ar rcs $(NAME) $(OBJS)

.PHONY:		clean

clean:
	rm -f ${OBJS}

fclean:		clean
	rm -f ${NAME}

re:			fclean all
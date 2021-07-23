# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rburton <rburton@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/28 11:32:38 by rburton           #+#    #+#              #
#    Updated: 2021/06/18 01:37:27 by rburton          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= m_paint.out

# HEADER		= m_paint.h
HEADER		= m_paint_test.h

# SRC 		= 	m_paint.c
SRC 		= 	m_paint_test.c

OBJS		= ${SRC:.c=.o}

GCC			= gcc

CFLAGS		= -g -Wall -Wextra -Werror

RM			= rm -f

all:		${NAME}

.c.o:		
				${GCC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:		${OBJS} ${HEADER}
				${GCC} ${CFLAGS} -o ${NAME} ${OBJS} -lm

clean:
		${RM} ${OBJS}

fclean:	clean
		${RM} ${NAME}
		${RM} ${LIB}

re:		fclean all
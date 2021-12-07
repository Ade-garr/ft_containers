# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/12 10:29:31 by user42            #+#    #+#              #
#    Updated: 2021/12/07 02:56:06 by ade-garr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS += srcs/main.cpp

OBJS	= ${SRCS:.cpp=.o}

NAME	= ft_containers_FT

INCLUDES = ./includes/

CC		= clang++

CFLAGS	+= -Wall
CFLAGS	+= -Wextra
CFLAGS	+= -Werror
CFLAGS	+= -std=c++98

HEADER += ${INCLUDES}enable_if.hpp
HEADER += ${INCLUDES}equal.hpp
HEADER += ${INCLUDES}iterator_traits.hpp
HEADER += ${INCLUDES}lexicographical_compare.hpp
HEADER += ${INCLUDES}map_iterators.hpp
HEADER += ${INCLUDES}map.hpp
HEADER += ${INCLUDES}pair.hpp
HEADER += ${INCLUDES}reverse_iterator.hpp
HEADER += ${INCLUDES}stack.hpp
HEADER += ${INCLUDES}vector_iterators.hpp
HEADER += ${INCLUDES}vector.hpp

all:		${NAME}

${NAME}:	${OBJS}
			${CC} ${CFLAGS} -I ${INCLUDES} ${OBJS} -o ${NAME}
			printf "\033[32m$@ is ready ! \n\033[0m"

${OBJS}: %.o: %.cpp ${HEADER}
			${CC} ${CFLAGS} -I ${INCLUDES} -c $< -o $@
			
clean:
			rm -f ${OBJS}

fclean:		clean
			rm -f ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
.SILENT:
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: guillemette.duchateau <guillemette.duch    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/22 18:38:46 by gduchate          #+#    #+#              #
#    Updated: 2023/04/06 20:32:23 by guillemette      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ircserv

SRC = ft_irc.cpp Client.cpp Server.cpp \
		Message.cpp Channel.cpp Command.cpp

OBJ = ${SRC:.cpp=.o}

HEADER = Replies.hpp Client.hpp Server.hpp \
		 Message.hpp Channel.hpp Command.hpp

CC = c++

FLAGS = -Wall -Wextra -Werror -std=c++98 -g

%.o : %.cpp ${HEADER}
	${CC} ${FLAGS} ${DEBUGFLAGS} -c $<

all : ${NAME}

${NAME} : ${OBJ}
		${CC} ${OBJ} ${FLAGS} ${DEBUGFLAGS} -o ${NAME}

clean :
		rm -f ${OBJ}

fclean : clean
		rm -f ${NAME}

re : fclean all

debug	: DEBUGFLAGS = -D DEBUG
debug	: all

.Phony : all clean fclean re
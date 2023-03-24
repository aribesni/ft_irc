# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: guillemette.duchateau <guillemette.duch    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/22 18:38:46 by gduchate          #+#    #+#              #
#    Updated: 2023/03/23 18:04:39 by guillemette      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ircserv

SRC = ft_irc.cpp Client.cpp Server.cpp \
		Message.cpp Channel.cpp Command.cpp

OBJ = ${SRC:.cpp=.o}

HEADER = Replies.hpp Client.hpp Server.hpp \
		 Message.hpp Channel.hpp Command.hpp

CC = c++

FLAGS = -Wall -Wextra -Werror -std=c++98

%.o : %.cpp
	${CC} ${FLAGS} -c $<

all : ${NAME}

${NAME} : ${OBJ}
		${CC} ${OBJ} ${FLAGS} -o ${NAME}

clean :
		rm -f ${OBJ}

fclean : clean
		rm -f ${NAME}

re : fclean all

.Phony : all clean fclean re
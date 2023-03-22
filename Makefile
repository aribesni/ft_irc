NAME = ircserv

SRC = ft_irc.cpp Client.cpp Server.cpp \
		bufferParser.cpp Message.cpp Command.cpp

OBJ = ${SRC:.cpp=.o}

HEADER = Replies.hpp Client.hpp Server.hpp \
			bufferParser.hpp Message.hpp Command.hpp

CC = c++

FLAGS = -Wall -Wextra -Werror -std=c++98

%.o : %.cpp ${HEADER}
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
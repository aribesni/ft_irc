NAME = ircserv

SRC = ft_irc.cpp Client.cpp Server.cpp \
		utils.cpp Command.cpp

OBJ = ${SRC:.cpp=.o}

HEADER = Replies.hpp Client.hpp Server.hpp utils.hpp

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
SRC=		srcs/test.cpp		\

OBJ=		$(SRC:.cpp=.o)

CPPFLAGS=	-I./includes		\

NAME=		portaudio

LIB=		-lrt -lasound -ljack -lpthread -I./includes -L./lib -lportaudio

$(NAME):	$(OBJ)
		g++ lib/libportaudio.a $(OBJ) -o $(NAME) $(LIB)

all:		$(NAME)

clean:
		rm -rf $(OBJ)

fclean:		clean
		rm -rf $(NAME)

re:		fclean all

.PHONY:		all fclean clean re

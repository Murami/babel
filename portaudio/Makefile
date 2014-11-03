SRC=		srcs/test2.cpp		\

OBJ=		$(SRC:.cpp=.o)

CPPFLAGS=	-I./includes		\

NAME=		portaudio

LIB=		-lrt -lasound -ljack -lpthread -I./includes -L./lib -lportaudio

$(NAME):	$(OBJ)
<<<<<<< HEAD
		g++ $(OBJ) -o $(NAME) $(LIB)
=======
		g++ -L./lib -lportaudio $(OBJ) -o $(NAME) $(LIB)
>>>>>>> 591ba75a12295c178a43545fd50ba47b1df46fa0

all:		$(NAME)

clean:
		rm -rf $(OBJ)

fclean:		clean
		rm -rf $(NAME)

re:		fclean all

.PHONY:		all fclean clean re

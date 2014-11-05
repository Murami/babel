SRC	=	main.cpp	\

NAME	=	server

OBJ	=	$(SRC:.cpp=.o)

CXX	=	g++

RM	=	rm -f

LDFLAGS	=	-lsfml-network -lsfml-system

$(NAME)	:	$(OBJ)
		$(CXX) $(OBJ) -o $(NAME) $(LDFLAGS)

all	:	$(NAME)

clean	:
		$(RM) $(OBJ)

fclean	:	clean
		$(RM) $(NAME)

re	:	fclean all

.PHONY	:	all clean fclean re

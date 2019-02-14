
PP	=	g++

NAME	=	example

CPPFLAGS	=	-W -Wall -Werror -Wextra -std=c++11 -lsfml-graphics -lsfml-system -lsfml-window -L../ -lReact-Views -I../src/Dom

RM	=	rm -f

SRCS	=	./Main.cpp

OBJS	=	$(SRCS:.cpp=.o)


all: $(NAME)

$(NAME): $(OBJS)
	$(PP) $(OBJS) -o $(NAME) $(CPPFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
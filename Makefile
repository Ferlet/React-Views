
PP	=	g++

NAME	=	demo

CPPFLAGS	=	-W -Wall -Werror -Wextra -std=c++11 -lsfml-graphics -lsfml-system -lsfml-window
CPPFLAGS	+=	-I./src/Dom -I./src/View

RM	=	rm -f

SRCS	=	src/mrp.cpp
SRCS	+=	src/View/View.cpp
SRCS	+=	src/Dom/Dom.cpp

OBJS	=	$(SRCS:.cpp=.o)

all: $(NAME) clean

$(NAME): $(OBJS)
	$(PP) -o $(NAME) $(OBJS) $(CPPFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

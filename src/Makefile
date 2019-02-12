
PP	=	g++

NAME	=	debug

CPPFLAGS	=	-W -Wall -Werror -Wextra -std=c++11 -lsfml-graphics -lsfml-system -lsfml-window
CPPFLAGS	+=	-I./Dom -I./View

RM	=	rm -f

SRCS	=	test.cpp
SRCS	+=	View/View.cpp
SRCS	+=	Dom/Dom.cpp

OBJS	=	$(SRCS:.cpp=.o)

all: $(NAME) clean

$(NAME): $(OBJS)
	$(PP) -o $(NAME) $(OBJS) $(CPPFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

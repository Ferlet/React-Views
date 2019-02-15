
PP	=	g++

NAME	=	libReact-Views.a

CPPFLAGS	=	-W -Wall -Werror -Wextra -std=c++11 -lsfml-graphics -lsfml-system -lsfml-window
CPPFLAGS	+=	-I./src/Dom -I./src/View -I./src/ImageView -I./src/xmlLib/

RM	=	rm -f

SRCS	=	src/Dom/Dom.cpp
SRCS	+=	src/View/View.cpp
SRCS	+=	src/ImageView/ImageView.cpp
SRCS	+= 	src/xmlLib/pugixml.cpp

OBJS	=	$(SRCS:.cpp=.o)


all: $(NAME)

$(NAME): $(OBJS)
	#$(PP) -o $(NAME) $(OBJS) $(CPPFLAGS) -shared
	ar crf $(NAME) $(OBJS)

%.o : %.cpp
	$(PP) $(CPPFLAGS) -c -fpic $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

PP	=	g++

NAME	=	libReact-Views.a

JSONLIB =	libstatic_Json.a

CPPFLAGS	=	-W -Wall -Werror -Wextra -std=c++14 -lsfml-graphics -lsfml-system -lsfml-window
CPPFLAGS	+=	-I./src/Dom -I./src/View -I./src/ImageView -I./src/xmlLib/
CPPFLAGS	+=  -I./src/jsonLib/Json/

RM	=	rm -f

SRCS	=	src/Dom/Dom.cpp
SRCS	+=	src/View/View.cpp
SRCS	+=	src/ImageView/ImageView.cpp
SRCS	+= 	src/xmlLib/pugixml.cpp
SRCS	+=	src/jsonLib/Json/src/Entity.cpp
SRCS	+=	src/jsonLib/Json/src/Parser.cpp

OBJS	=	$(SRCS:.cpp=.o)


all: $(NAME)

$(NAME): $(OBJS)
	ar crf $(NAME) $(OBJS)

%.o : %.cpp
	$(PP) $(CPPFLAGS) -c -fpic $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
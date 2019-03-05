
PP	=	g++

NAME	=	libReact-Views.a

JSONLIB =	libstatic_Json.a

CPPFLAGS	=	-W -Wall -Werror -Wextra -std=c++11 -lsfml-graphics -lsfml-system -lsfml-window
CPPFLAGS	+=	-I./src/Dom -I./src/View -I./src/ImageView -I./src/xmlLib/
CPPFLAGS	+=  -I./src/jsonLib/Json-master/srcs/Entity/

RM	=	rm -f

SRCS	=	src/Dom/Dom.cpp
SRCS	+=	src/View/View.cpp
SRCS	+=	src/ImageView/ImageView.cpp
SRCS	+= 	src/xmlLib/pugixml.cpp

OBJS	=	$(SRCS:.cpp=.o)


all: jsonLib $(NAME)

$(NAME): $(OBJS)
	ar -x $(JSONLIB)
	ar crf $(NAME) $(OBJS) *.o

%.o : %.cpp
	$(PP) $(CPPFLAGS) -c -fpic $< -o $@

clean:
	$(MAKE) -C src/jsonLib/Json-master/ clean
	$(RM) $(OBJS)
	$(RM) *.o

fclean: clean
	$(MAKE) -C src/jsonLib/Json-master/ fclean
	$(RM) $(NAME)
	$(RM) $(JSONLIB)

re: fclean all




jsonLib:
	$(MAKE) -C src/jsonLib/Json-master/
	mv src/jsonLib/Json-master/$(JSONLIB) ./
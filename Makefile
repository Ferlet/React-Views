
PP	=	g++

NAME	=	libReact-Views.a

CPPFLAGS	=	-W -Wall -Werror -Wextra -std=c++11 -lsfml-graphics -lsfml-system -lsfml-window
CPPFLAGS	+=	-I./src/Dom -I./src/View -I./src/ImageView -I./src/xmlLib/ -L./src/jsonLib/Json-master/ -lstatic_Json

RM	=	rm -f

SRCS	=	src/Dom/Dom.cpp
SRCS	+=	src/View/View.cpp
SRCS	+=	src/ImageView/ImageView.cpp
SRCS	+= 	src/xmlLib/pugixml.cpp

OBJS	=	$(SRCS:.cpp=.o)


all: jsonLib $(NAME)

once: 
	$(RM) $(OBJS)
	$(RM) $(NAME)
	$(MAKE) $(NAME)

$(NAME): $(OBJS)
	ar crf $(NAME) $(OBJS)

%.o : %.cpp
	$(PP) $(CPPFLAGS) -c -fpic $< -o $@

clean:
	$(MAKE) -C src/jsonLib/Json-master/ clean
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) -C src/jsonLib/Json-master/ fclean
	$(RM) $(NAME)

re: fclean all




jsonLib:
	$(MAKE) -C src/jsonLib/Json-master/
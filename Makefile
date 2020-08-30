CC	=	g++

RM	=	rm -f

LDFLAGS	+=	-ldl -std=c++11

CXXFLAGS +=	-fPIC -std=c++11 -g3

#-----------------------START-EXE------------------------#

NAME	=	arcade

SRC	=	main.cpp	\
		Arcade.cpp

OBJ	=	$(SRC:.cpp=.o)

#-----------------------END-EXE------------------------#


#-----------------------START-LIB------------------------#
#------------------START-NCURSES-------------------#
NAME_LIB_NCURSES	=	./lib/lib_arcade_ncurses.so

SRC_LIB_NCURSES		=	./lib/Ncurses.cpp	\
				./Leaderboard.cpp

OBJ_LIB_NCURSES		=	$(SRC_LIB_NCURSES:.cpp=.o)
#------------------END-NCURSES-------------------#

#------------------START-SFML-------------------#
NAME_LIB_SFML		=	./lib/lib_arcade_sfml.so

SRC_LIB_SFML		=	./lib/Sfml.cpp		\
				./Leaderboard.cpp	\

OBJ_LIB_SFML		=	$(SRC_LIB_SFML:.cpp=.o)
#------------------END-SFML-------------------#

#------------------START-LAPIN-------------------#
NAME_LIB_LAPIN		=	./lib/lib_arcade_lapin.so

SRC_LIB_LAPIN		=	./lib/Lapin.cpp		\
				./Leaderboard.cpp

OBJ_LIB_LAPIN		=	$(SRC_LIB_LAPIN:.cpp=.o)
#------------------END-LAPIN-------------------#
#-----------------------END-LIB------------------------#


#-----------------------START-GAME------------------------#
#------------------START-SNAKE-------------------#
NAME_LIB_SNAKE		=	./games/lib_arcade_snake.so

SRC_LIB_SNAKE		=	./games/Snake.cpp	\

OBJ_LIB_SNAKE		=	$(SRC_LIB_SNAKE:.cpp=.o)
#------------------END-SNAKE-------------------#

#------------------START-CENTIPED-------------------#
NAME_LIB_CENTIPED	=	./games/lib_arcade_centipede.so

SRC_LIB_CENTIPED	=	./games/Centiped.cpp	\

OBJ_LIB_CENTIPED	=	$(SRC_LIB_CENTIPED:.cpp=.o)
#------------------END-CENTIPED-------------------#
#------------------START-PACMAN-------------------#
NAME_LIB_PACMAN		=	./games/lib_arcade_pacman.so

SRC_LIB_PACMAN		=	./games/Pacman.cpp	\

OBJ_LIB_PACMAN		=	$(SRC_LIB_PACMAN:.cpp=.o)
#------------------END-PACMAN-------------------#

#------------------START-NIBBLER-------------------#
NAME_LIB_NIBBLER	=	./games/lib_arcade_nibbler.so

SRC_LIB_NIBBLER		=	./games/Nibbler.cpp	\

OBJ_LIB_NIBBLER		=	$(SRC_LIB_NIBBLER:.cpp=.o)
#------------------END-NIBBLER-------------------#

#-----------------------END-GAME------------------------#

all:			$(NAME) $(NAME_LIB_NCURSES) $(NAME_LIB_SFML) $(NAME_LIB_LAPIN) $(NAME_LIB_SNAKE) $(NAME_LIB_CENTIPED) $(NAME_LIB_PACMAN) $(NAME_LIB_NIBBLER)

$(NAME):		$(OBJ)
			$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

$(NAME_LIB_NCURSES):	$(OBJ_LIB_NCURSES)
			$(CC) -shared -o $(NAME_LIB_NCURSES) $(OBJ_LIB_NCURSES) -lncurses

$(NAME_LIB_SFML):	$(OBJ_LIB_SFML)
			$(CC) -shared -o $(NAME_LIB_SFML) $(OBJ_LIB_SFML) -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

$(NAME_LIB_LAPIN):	$(OBJ_LIB_LAPIN)
			$(CC) -shared -o $(NAME_LIB_LAPIN) $(OBJ_LIB_LAPIN) -L/home/${USER}/.froot/lib/ -llapin \
                        -L/usr/local/lib \
                        -lsfml-audio \
                        -lsfml-graphics \
                        -lsfml-window \
                        -lsfml-system \
                        -lstdc++ -ldl \
                        -lm

$(NAME_LIB_SNAKE):	$(OBJ_LIB_SNAKE)
			$(CC) -shared -o $(NAME_LIB_SNAKE) $(OBJ_LIB_SNAKE)

$(NAME_LIB_CENTIPED):	$(OBJ_LIB_CENTIPED)
			$(CC) -shared -o $(NAME_LIB_CENTIPED) $(OBJ_LIB_CENTIPED)

$(NAME_LIB_PACMAN):	$(OBJ_LIB_PACMAN)
			$(CC) -shared -o $(NAME_LIB_PACMAN) $(OBJ_LIB_PACMAN)

$(NAME_LIB_NIBBLER):	$(OBJ_LIB_NIBBLER)
			$(CC) -shared -o $(NAME_LIB_NIBBLER) $(OBJ_LIB_NIBBLER)

clean:
			$(RM) $(OBJ) $(OBJ_LIB_NCURSES) $(OBJ_LIB_SFML) $(OBJ_LIB_LAPIN) $(OBJ_LIB_SNAKE) $(OBJ_LIB_CENTIPED) $(OBJ_LIB_PACMAN) $(OBJ_LIB_NIBBLER)

fclean:			clean
			$(RM) $(NAME) $(NAME_LIB_NCURSES) $(NAME_LIB_SFML) $(NAME_LIB_LAPIN) $(NAME_LIB_SNAKE) $(NAME_LIB_CENTIPED) $(NAME_LIB_PACMAN) $(NAME_LIB_NIBBLER)

re:			fclean all

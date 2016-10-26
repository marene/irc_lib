NAME =				test
SRCS_DIR =			./srcs/
INCLUDES_DIR =		./includes/
IRCLIB_DIR =		/Users/marene/projects/irc_lib/
IRCLIB_INCLUDES =	../includes/
IRCLIB =			irclib
OBJ_DIR =			./obj/
SRCS =				main.cpp
OBJ =				$(SRCS:.cpp=.o)
CC =				clang++
CFLAGS =			-Wall -Wextra -Werror -std=c++11 -g -I $(INCLUDES_DIR) -I $(IRCLIB_INCLUDES) -o
LDFLAGS =			-L$(IRCLIB_DIR) -l$(IRCLIB) -o

all: $(OBJ_DIR) $(LIBFT_NAME) $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(NAME): $(addprefix $(OBJ_DIR), $(OBJ))
	$(CC) $(LDFLAGS) $@ $^

$(OBJ_DIR)%.o: $(SRCS_DIR)%.cpp
	$(CC) $(CFLAGS) $@ -c $<

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re unit $(UNIT_NAME)

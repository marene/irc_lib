NAME =				libirclib.so
CURRENT_VERSION =	0.1
INSTALL_PATH =		/Users/marene/projects/irc_lib
SRCS_DIR =			./srcs/
INCLUDES_DIR =		./includes/
OBJ_DIR =			./obj/
SRCS =				Buffer.cpp\
					IrcClient.cpp\
					Socket.cpp

OBJ =				$(SRCS:.cpp=.o)
CC =				clang++
CFLAGS =			-Wall -Wextra -Werror -std=c++11 -g -I $(INCLUDES_DIR) -o
LDFLAGS =			-dynamiclib -install_name $(INSTALL_PATH)/$(NAME) -current_version $(CURRENT_VERSION) -o

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

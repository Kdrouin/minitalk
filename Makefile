NAME_CLIENT = client
NAME_SERVER = server
PRINTF = includes/ft_printf

SRC_CLIENT = src/client.c
SRC_SERVER = src/server.c
SRC_UTILS = $(wildcard src/utils*.c)

OBJ_CLIENT = $(SRC_CLIENT:.c=.o)
OBJ_SERVER = $(SRC_SERVER:.c=.o)
OBJ_UTILS = $(patsubst %.c, %.o, $(SRC_UTILS))

CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: $(PRINTF)/libftprintf.a $(NAME_CLIENT) $(NAME_SERVER)

$(PRINTF)/libftprintf.a:
	make -C $(PRINTF)
	echo "libftprintf.a created"

$(NAME_CLIENT): $(OBJ_CLIENT) $(OBJ_UTILS)
	$(CC) $(CFLAGS) -o $(NAME_CLIENT) $(OBJ_CLIENT) $(OBJ_UTILS) -L$(PRINTF) -lftprintf

$(NAME_SERVER): $(OBJ_SERVER) $(OBJ_UTILS)
	$(CC) $(CFLAGS) -o $(NAME_SERVER) $(OBJ_SERVER) $(OBJ_UTILS) -L$(PRINTF) -lftprintf

clean:
	rm -f $(OBJ_CLIENT) $(OBJ_SERVER) $(OBJ_UTILS)

fclean: clean
	make -C $(PRINTF) fclean
	rm -f $(NAME_CLIENT) $(NAME_SERVER)

re: fclean all

.PHONY: all clean fclean re

SRC = push_swap.c
OBJ = $(SRC:.c=.o)

NAME = push_swap

CFLAGS = -Wall -Wextra -Werror

LIB = libft/libft.a

all: $(NAME)

$(NAME): $(LIB) $(OBJ)
	cc $(CFLAGS) $(OBJ) $(LIB) -o $@

$(LIB):
	make -C libft

%.o: %.c
	cc $(CFLAGS) -c $< -o $@

clean:
	make -C libft clean
	rm -f $(OBJ)

fclean: clean
	make -C libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re


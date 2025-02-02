SRC = push_swap.c\
	  parse_input.c\
	  trivial.c\
	  complex.c\
	  move.c\
	  target.c\
	  cost.c\
	  util.c\
	  instructions/push.c\
	  instructions/swap.c\
	  instructions/rotate.c
OBJ = $(SRC:.c=.o)

NAME = push_swap

LIBDIR = libft
LIBNAME = ft
LIB = $(LIBDIR)/lib$(LIBNAME).a

CFLAGS = -Wall -Wextra -Werror # -fsanitize=address -g3

all: $(NAME)

$(NAME): $(LIB) $(OBJ)
	cc $(CFLAGS) $(OBJ) -L$(LIBDIR) -l$(LIBNAME) -o $@

$(LIB):
	@$(MAKE) --no-print-directory -C $(LIBDIR)

%.o: %.c
	cc $(CFLAGS) -I$(LIBDIR) -c $< -o $@

clean:
	@$(MAKE) --no-print-directory -C libft clean
	@rm -f $(OBJ)

fclean: clean
	@$(MAKE) --no-print-directory -C libft fclean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

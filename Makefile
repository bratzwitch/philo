NAME = philo

CFLAGS = -Wall -Wextra -Werror -pthread

LIBFT = ./lib_ft

SRC =	philosophers.c

OBJS = $(SRC:.c=.o)

RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
		@echo "Compiling this crap"
		cc $(CFLAGS) $(OBJS) -o $(NAME)
		make clean
		@echo "All good you can rest(no)"
clean:
		$(RM) $(OBJS)

fclean:	clean
		$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

.SILENT:
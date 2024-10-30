NAME = philo

CFLAGS = -Wall -Wextra -Werror 

LIBFT = ./lib_ft

SRC =	main.c	checkers.c avg_it_job_seeker.c	init.c	exec.c	time.c
			

OBJS = $(SRC:.c=.o)

RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
		@echo "Compiling this crap"
		cc -pthread $(CFLAGS) $(OBJS) -o $(NAME)
		make clean
		@echo "All good you can rest(no)"
clean:
		$(RM) $(OBJS)

fclean:	clean
		$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

.SILENT:
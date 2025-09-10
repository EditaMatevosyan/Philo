NAME = philo

CC = CC

CFLAGS = -Wall -Wextra -Werror #-g3 -fsanitize=thread

HEADERS = inc/philo.h

SRCS_DIR = src/

OBJS_DIR = objs/

SRCS_NAME = main.c\
			init_vars.c\
			simulation.c\
			checks.c\
			utils.c\

OBJS = $(addprefix $(OBJS_DIR), $(OBJS_NAME))
OBJS_NAME = $(SRCS_NAME:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) -lpthread

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(HEADERS) Makefile
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: clean all

.PHONY: all clean fclean re
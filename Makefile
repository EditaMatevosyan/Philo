NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinc #-g3 -fsanitize=thread

HEADERS = inc/philo.h

SRCS_DIR = src/
OBJS_DIR = objs/

SRCS_NAME = main.c \
			init.c \
			validation.c \
			actions.c \
			ft_atol.c \
			routine.c \

OBJS_NAME = $(SRCS_NAME:.c=.o)
OBJS = $(addprefix $(OBJS_DIR), $(OBJS_NAME))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ -lpthread

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(HEADERS) Makefile | $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

# Makefile for minishell project

NAME = minishell

SRCS = main.c \
       shell.c \
       builtin.c \
       execute.c \
       # add other source files here

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror
LIBFT = ./libft/libft.a
READLINE = -lreadline

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(READLINE)

$(LIBFT):
	make -C ./libft

clean:
	rm -f $(OBJS)
	make clean -C ./libft

fclean: clean
	rm -f $(NAME)
	make fclean -C ./libft

re: fclean all

.PHONY: all clean fclean re

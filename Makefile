NAME = pipex
CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRCS_DIR = sources
SRCS =  pipex.c get_path.c utils.c ft_putchar_fd.c \
		ft_putstr_fd.c ft_split.c ft_strchr.c \
		ft_strdup.c ft_strjoin.c ft_strlcat.c \
		ft_strlcpy.c ft_strlen.c ft_strncmp.c \
		ft_putendl_fd.c

OBJS_DIR = $(SRCS_DIR)/.objs
OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -I./includes -c $< -o $@

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

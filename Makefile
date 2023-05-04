NAME = pipex
CC = clang #-g -fsanitize=address
CFLAGS = -I./includes

SRCS_DIR = sources
SRCS =  pipex.c get_path.c utils.c ft_putchar_fd.c \
		ft_putstr_fd.c ft_split.c ft_strchr.c \
		ft_strdup.c ft_strjoin.c ft_strlcat.c \
		ft_strlcpy.c ft_strlen.c ft_strncmp.c \
		ft_putendl_fd.c

OBJS_DIR = $(SRCS_DIR)/.objs
OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS) $(OBJS_LIBFT)
	@$(CC) $(OBJS) $(LFLAGS) -o $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(OBJS_DIR)
	@echo "Compiling $< \033[0;32m✔\033[0m"
	@$(CC) -Wall -Wextra -Werror -I/usr/include -O3 $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJS_DIR)
	@echo "===> Objects deleted"

fclean: clean
	@rm -f $(NAME)
	@echo "===> Binaries deleted"

re: fclean all

.PHONY: all clean fclean re

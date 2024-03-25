NAME := libft.a
SRC := ft_isalnum.c \
	ft_isalpha.c \
	ft_isdigit.c \
	ft_putchar_fd.c \
	ft_putendl_fd.c \
	ft_putstr_fd.c \
	ft_strchr.c \
	ft_strjoin.c \
	ft_strlcpy.c \
	ft_strlen.c \
	ft_substr.c
OBJ := $(SRC:%.c=%.o)
CC := cc
CFLAGS := -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
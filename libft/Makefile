NAME := libft.a
SRC := ft_printf.c \
	ft_strjoin.c \
	ft_strchr.c \
	ft_substr.c \
	ft_strlen.c \
	ft_strlcpy.c
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
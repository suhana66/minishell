NAME := minishell
CC := cc
CFLAGS := -Wall -Wextra -Werror

LIBFT_PATH := libft
LIBFT := $(LIBFT_PATH)/libft.a
LIBFT_LINK := -L$(LIBFT_PATH) -lft

SRC := minishell.c
OBJ := $(SRC:%.c=%.o)
INCLUDES := -I$(LIBFT_PATH)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $(OBJ) $(LIBFT_LINK)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_PATH)

clean:
	make clean -C $(LIBFT_PATH)
	rm -f $(OBJ)

fclean: clean
	make fclean -C $(LIBFT_PATH)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
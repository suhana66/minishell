NAME := minishell
CC := cc
CFLAGS := -Wall -Wextra -Werror -Wfatal-errors

LIBFT_PATH := libft
LIBFT := $(LIBFT_PATH)/libft.a
LIBFT_LINK := -L$(LIBFT_PATH) -lft

READLINE_LIBRARY := -lreadline

MAIN_SRCS := \
	utils.c \
	cmd_utils.c \
	find_pwd.c \
	lexer.c \
	main.c \
	parse_env.c \
	parser.c \
	token_utils.c

BUILTIN_PATH := builtin
BUILTIN_SRCS := \
	$(BUILTIN_PATH)/builtin_utils.c \
	$(BUILTIN_PATH)/mini_cd.c \
	$(BUILTIN_PATH)/mini_echo.c \
	$(BUILTIN_PATH)/mini_env.c \
	$(BUILTIN_PATH)/mini_exit.c \
	$(BUILTIN_PATH)/mini_export.c \
	$(BUILTIN_PATH)/mini_pwd.c \
	$(BUILTIN_PATH)/mini_unset.c

SRC := $(BUILTIN_SRCS) $(MAIN_SRCS)
OBJ := $(SRC:%.c=%.o)
INCLUDES := -I$(LIBFT_PATH) -I$(BUILTIN_PATH) -I.

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $(OBJ) $(LIBFT_LINK) $(READLINE_LIBRARY)

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
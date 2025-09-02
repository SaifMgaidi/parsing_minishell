NAME = lex

CC = cc
CFLAGS = -g -fsanitize=address -fsanitize=leak -Wall -Wextra -Werror -I.

RM = rm -f

SRC_DIR = ./lexer
SRC = $(SRC_DIR)/lexer.c \
	  $(SRC_DIR)/lexer_utils.c \
	  $(SRC_DIR)/extract_word.c \
	  $(SRC_DIR)/utils.c

OBJ = $(SRC:.c=.o)

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -L$(LIBFT_DIR) -lft -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	$(RM) $(OBJ)
	make -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
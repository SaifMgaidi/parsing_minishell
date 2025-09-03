NAME = run

CC = cc
CFLAGS = -g -fsanitize=address -fsanitize=leak -Wall -Wextra -Werror -I.

RM = rm -f

SRC_DIR_LEXER = ./lexer
SRC_DIR_PARSER = ./parser
SRC = $(SRC_DIR_LEXER)/lexer.c \
	  $(SRC_DIR_LEXER)/lexer_utils.c \
	  $(SRC_DIR_LEXER)/extract_word.c \
	  $(SRC_DIR_LEXER)/utils.c \
	  $(SRC_DIR_PARSER)/parser.c \
	  $(SRC_DIR_PARSER)/parser_utils.c

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
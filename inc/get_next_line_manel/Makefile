NAME = libftgetnextline.a

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRC_DIR = .

SRCS = get_next_line.c get_next_line_utils.c

OBJS = $(SRCS:%.c=$(SRC_DIR)/%.o)

$(NAME): $(OBJS)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)

all: $(NAME)

#$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
#	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

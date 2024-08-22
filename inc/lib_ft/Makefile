# Name of the library
NAME = libft.a

# Compiler
CC = cc

# Directory containing the source files
SRC_DIR = .

# Compiler flags
CFLAGS = -Wall -Wextra -Werror -g

# Source files to be compiled into objects
SRCS = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
	ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
	ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
	ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c \
	ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c \
	ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c \
	get_next_line.c get_next_line_utils.c


# Source files for the bonus part
BONUS_SRCS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
	ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c \
	ft_lstiter.c ft_lstmap.c

# Object files generated from source files
OBJS = $(SRCS:%.c=$(SRC_DIR)/%.o)
BONUS_OBJS = $(BONUS_SRCS:%.c=$(SRC_DIR)/%.o)

# Directory containing header files
INC_DIR = .

# Rule to compile individual source files into object files
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to create the target library
$(NAME): $(OBJS)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)

# Rule to build the library
all: $(NAME)

#Rule to build the bonus part
bonus: $(BONUS_OBJS)
	@ar rc $(NAME) $(BONUS_OBJS)
	@ranlib $(NAME)

# Rule to remove object files
clean:
	@rm -f $(OBJS) $(BONUS_OBJS)

# Rule to remove object files and the target library
fclean: clean
	@rm -f $(NAME) $(BONUS_OBJS)

# Rule to perform a full rebuild
re: fclean all

# Default target
.DEFAULT_GOAL := all

#PHONY
.PHONY: all bonus clean fclean re

# End of Makefile

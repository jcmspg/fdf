NAME = fdf
CC = cc
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address
POSTCC = -I $(INC_DIR) -I $(SRC_DIR) \
         -L $(INC_DIR)/minilibx-linux -lmlx -lX11 -lXext -lm \
         -L $(INC_DIR)/lib_ft -lft \


SRC_DIR = ./src
OBJ_DIR = ./obj
INC_DIR = ./inc

# List of all .c files in the src directory
SRC_FILES = ./src/debug_utils.c ./src/lookup_tables.c ./src/conic_utils.c ./src/scale_normalization_utils.c ./src/spherical_utils2.c ./src/spherical_utils3.c ./src/data_utils.c ./src/display_utils.c ./src/draw_line.c ./src/grid_utils.c ./src/help_utils.c ./src/main.c ./src/math_utils.c ./src/mode_utils.c ./src/move_utils.c ./src/parsing_utils.c ./src/point_utils.c ./src/projection_utils.c ./src/rotation_utils.c ./src/scale_utils.c ./src/spherical_utils.c ./src/free_utils.c ./src/gui_utils.c ./src/mlx_utils.c ./src/color_utils.c ./src/bresen_utils.c ./src/draw_sphere_utils.c ./src/color_grad_utils.c ./src/color_grayscale_utils.c ./src/point_maker_utils.c ./src/margin_utils.c ./src/gui_info_utils.c ./src/math_utils2.c ./src/math_utils3.c ./src/mode_utils2.c ./src/mode_utils3.c ./src/mode_utils4.c ./src/move_utils2.c ./src/parsing_utils2.c ./src/parsing_utils3.c ./src/parsing_utils4.c ./src/point_utils2.c ./src/rotation_utils_x.c ./src/rotation_utils_y.c ./src/rotation_utils_z.c ./src/scale_utils2.c ./src/spherical_utils4.c

# List of all .o files in the obj directory
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Pattern rule to compile each .c file into an .o file
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I $(INC_DIR) -I $(SRC_DIR) -c $< -o $@

# Rule to create the final executable
$(NAME): $(OBJ_FILES)
	@echo "Building $(NAME)..."
	@make -C $(INC_DIR)/lib_ft > /dev/null 2>&1 || { echo "Failed to build lib_ft"; exit 1; }
	@make -C $(INC_DIR)/minilibx-linux > /dev/null 2>&1 || { echo "Failed to build minilibx-linux"; exit 1; }
	@$(CC) $(CFLAGS) $(OBJ_FILES) \
		$(INC_DIR)/lib_ft/libft.a \
		$(POSTCC) -o $(NAME) || { echo "Linking failed."; exit 1; }
	@echo "Compilation complete. Executable: $(NAME)"

all:  $(NAME)

bonus: all

clean:
	@rm -rf $(OBJ_DIR) sources.mk
	@make clean -C $(INC_DIR)/lib_ft > /dev/null 2>&1
	@make clean -C $(INC_DIR)/minilibx-linux > /dev/null 2>&1
	@echo "Clean complete."

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(INC_DIR)/lib_ft > /dev/null 2>&1 || make clean -C $(INC_DIR)/lib_ft > /dev/null 2>&1
	@make clean -C $(INC_DIR)/minilibx-linux > /dev/null 2>&1
	@echo "Full clean complete."

re: fclean all

.PHONY: all clean fclean re

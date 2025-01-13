# Name: raycasting
NAME = cub3d_prueba

# Compiler
CC = clang

# Compiler flags
FLAGS = -g -Wall -Werror -Wextra -Iinclude #-fsanitize=address

# GLFW for MLX42 linux
GLFW = -ldl -lglfw -pthread -lm 

# Source files for libft
LIBFT_PATH = ./Libft

# Compiled libft
LIBFT = $(LIBFT_PATH)/libft.a

# Source files for mlx42
MLX_PATH = ./MLX42

# Compiled mlx42
MLX = $(MLX_PATH)/libmlx42.a

# Source files for mandatory
FILES = drawing.c cub3d.c movement.c render.c textures.c mov_forward.c turn_mov.c side_mov.c key_a.c\
		wall_texture.c

# Object files
OBJS = $(FILES:.c=.o)

# Compile rule
%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@

# Build rule for mandatory
$(NAME): $(LIBFT) $(MLX) $(OBJS)
	@$(CC) $(FLAGS) $(GLFW) $(OBJS) $(LIBFT) $(MLX) -o $(NAME)
	@echo "cub3d created"

# Build rule for libft
$(LIBFT):
	@make -C $(LIBFT_PATH) all

# Build rule for mlx42
$(MLX):
	@make -C $(MLX_PATH) all

# Build rule for mandatory
all: $(NAME)

# Clean rule
clean: 
	@rm -f $(OBJS)
	@make -C $(LIBFT_PATH) clean
	@make -C $(MLX_PATH) clean

# Fclean rule
fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_PATH) fclean
	@make -C $(MLX_PATH) clean # Cambiado de fclean a clean

# Re rule
re: fclean all

.PHONY = all clean fclean re libft
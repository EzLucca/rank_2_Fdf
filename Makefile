CC       := cc
CFLAGS   := -Wall -Wextra -Werror -O3
LDFLAGS  := -ldl -lglfw -lm

NAME     := fdf

SRC_DIR     := src
BUILD_DIR   := build
OBJ_DIR     := $(BUILD_DIR)/src
INCLUDES    := -I include -I lib/MLX42/include -I lib/libft/include

LIBFT_DIR   := lib/libft
LIBFT_A     := $(LIBFT_DIR)/libft.a
MLX_DIR     := lib/MLX42
MLX_A       := $(BUILD_DIR)/mlx42/libmlx42.a

SRC      := $(wildcard $(SRC_DIR)/*.c)
OBJ      := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

GREEN = \033[0;32m

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_A) $(MLX_A)
	@$(CC) $(OBJ) $(LIBFT_A) $(MLX_A) $(LDFLAGS) -o $@
	@echo "✅ Build $(GREEN)$(NAME) successfully! 🎉"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $@

$(LIBFT_A):
	@make --no-print-directory -C $(LIBFT_DIR)

$(MLX_A):
	@cmake -S $(MLX_DIR) -B $(BUILD_DIR)/mlx42
	@make --no-print-directory -C $(BUILD_DIR)/mlx42 -j4

clean:
	@rm -rf $(BUILD_DIR)
	@make --no-print-directory -C $(LIBFT_DIR) clean
	@echo "🧹 Removed directory $(GREEN) $(BUILD_DIR)."

fclean: clean
	@rm -rf $(NAME)
	@make --no-print-directory fclean -C $(LIBFT_DIR)
	@echo "🧹 Removed executable $(GREEN) $(NAME)."

re: fclean all

.PHONY: all clean fclean re

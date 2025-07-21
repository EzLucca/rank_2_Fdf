CC       := cc
CFLAGS   := -O0 -g -Wall -Wextra -Werror 
LDFLAGS  := -ldl -lglfw -lm

NAME     := fdf

SRC_DIR     := src
BUILD_DIR   := build
OBJ_DIR     := $(BUILD_DIR)/src
INCLUDES    := -I include -I lib/MLX42/include -I lib/libft/include

LIBFT_DIR   := lib/libft
LIBFT_A     := $(LIBFT_DIR)/libft.a
MLX_REPO	:= https://github.com/codam-coding-college/MLX42.git
MLX_DIR     := lib/MLX42
MLX_A       := $(BUILD_DIR)/mlx42/libmlx42.a

SRC      := $(wildcard $(SRC_DIR)/*.c)
OBJ      := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(LIBFT_A) $(MLX_A) $(NAME)

$(LIBFT_A):
	@make --no-print-directory -C $(LIBFT_DIR)

$(MLX_A):
	@if [ ! -d "$(MLX_DIR)" ]; then \
		git clone $(MLX_REPO) $(MLX_DIR); \
		fi;
	@cmake -S $(MLX_DIR) -B $(BUILD_DIR)/mlx42
	@make --no-print-directory -C $(BUILD_DIR)/mlx42 -j4

$(NAME): $(OBJ) $(LIBFT_A) $(MLX_A)
	@$(CC) $(OBJ) $(LIBFT_A) $(MLX_A) $(LDFLAGS) -o $@
	@clear
	@echo "✅ Build $(NAME) successfully! 🎉"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $@

clean:
	rm -rf $(BUILD_DIR)
	@make --no-print-directory -C $(LIBFT_DIR) clean

fclean: clean
	rm -rf $(NAME) $(MLX_DIR)
	@make --no-print-directory fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re

CC       := cc
CFLAGS   := -g -Wall -Wextra -Werror
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

SRC      := $(SRC_DIR)/checks.c \
			$(SRC_DIR)/color.c \
			$(SRC_DIR)/draw.c \
			$(SRC_DIR)/hooks.c \
			$(SRC_DIR)/loop.c \
			$(SRC_DIR)/main.c \
			$(SRC_DIR)/parsing.c \
			$(SRC_DIR)/rotations.c \
			$(SRC_DIR)/utils.c \
			$(SRC_DIR)/init.c \

OBJ      := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(LIBFT_A) $(MLX_A) $(NAME)

$(LIBFT_A):
	@make --no-print-directory -C $(LIBFT_DIR)

$(MLX_A):
	@if [ ! -d "$(MLX_DIR)" ]; then \
		echo "Cloning MLX42 repository..."; \
		git clone $(MLX_REPO) $(MLX_DIR); \
		cmake -S $(MLX_DIR) -B $(BUILD_DIR)/mlx42; \
		make --no-print-directory -C $(BUILD_DIR)/mlx42 -j4; \
		fi;

$(NAME): $(LIBFT_A) $(MLX_A) $(OBJ)
	@$(CC) $(OBJ) $(LIBFT_A) $(MLX_A) $(LDFLAGS) -o $@
	@clear
	@echo "✅ Build $(NAME) successfully! 🎉"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $@

clean:
	rm -rf $(OBJ_DIR) $(BUILD_DIR)/src
	@make --no-print-directory -C $(LIBFT_DIR) clean

fclean: clean
	rm -rf $(NAME) $(BUILD_DIR) $(MLX_DIR)
	@make --no-print-directory fclean -C $(LIBFT_DIR)

re: fclean all

.SECONDARY: $(OBJS)
.PHONY: all clean fclean re

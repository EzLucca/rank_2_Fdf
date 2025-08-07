CC       := cc
CFLAGS   := -Wall -Wextra -Werror -o3
LDFLAGS  := -ldl -lglfw -lm

NAME     		:= fdf
NAME_BONUS		:= fdf_bonus

SRC_DIR     := src
BUILD_DIR   := build
OBJ_DIR     := $(BUILD_DIR)/src
INCLUDES    := -I include -I lib/MLX42/include -I lib/libft/include

SRC_DIR_BONUS     := src_bonus
OBJ_DIR_BONUS     := $(BUILD_DIR)/src_bonus

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

SRC_BONUS      := $(SRC_DIR_BONUS)/checks_bonus.c \
				  $(SRC_DIR_BONUS)/color_bonus.c \
				  $(SRC_DIR_BONUS)/draw_bonus.c \
				  $(SRC_DIR_BONUS)/hooks_bonus.c \
				  $(SRC_DIR_BONUS)/loop_bonus.c \
				  $(SRC_DIR_BONUS)/main_bonus.c \
				  $(SRC_DIR_BONUS)/parsing_bonus.c \
				  $(SRC_DIR_BONUS)/rotations_bonus.c \
				  $(SRC_DIR_BONUS)/utils_bonus.c \
				  $(SRC_DIR_BONUS)/init_bonus.c \

OBJ      := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJ_BONUS := $(SRC_BONUS:$(SRC_DIR_BONUS)/%.c=$(OBJ_DIR_BONUS)/%.o)

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

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(LIBFT_A) $(MLX_A) $(OBJ_BONUS)
	@$(CC) $(OBJ_BONUS) $(LIBFT_A) $(MLX_A) $(LDFLAGS) -o $@
	@clear
	@echo "✅ Build $(NAME_BONUS) successfully! 🎉"

$(OBJ_DIR_BONUS)/%.o: $(SRC_DIR_BONUS)/%.c | $(OBJ_DIR_BONUS)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR_BONUS):
	@mkdir -p $@

clean:
	rm -rf $(OBJ_DIR) $(BUILD_DIR)/src
	@make --no-print-directory -C $(LIBFT_DIR) clean

fclean: clean
	rm -rf $(NAME) $(NAME_BONUS) $(BUILD_DIR) $(MLX_DIR)
	@make --no-print-directory fclean -C $(LIBFT_DIR)

re: fclean all

.SECONDARY: $(OBJ)
.SECONDARY: $(OBJ_BONUS)
.PHONY: all clean fclean re bonus

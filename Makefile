NAME	:= fdf 

LIBFT_DIR := libft
LIBFT := $(LIBFT_DIR)/libft.a

CFLAGS	:= -Wextra -Wall -Werror -Wunreachable-code -Ofast -I$(INCLUDE_DIR)
C_MLX := $(MLX_LIB) -Iinclude -ldl -lglfw -pthread -lm


MLX_REPO := https://github.com/codam-coding-college/MLX42.git
MLX_DIR := MLX42
MLX_BUILD_DIR := build
MLX_LIB := $(MLX_DIR)/$(MLX_BUILD_DIR)/libmlx42.a

INCLUDE_DIR	:= ./include
LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
SRCS	:= $(shell find ./src -iname "*.c")
OBJS	:= ${SRCS:.c=.o}

all: $(NAME)

$(LIBFT):
	@make --no-print-directory -C $(LIBFT_DIR)

$(MLX_LIB):
	if ! find . | grep MLX42; then \
		git clone $(MLX_REPO) $(MLX_DIR);\
	fi;
	@cd $(MLX_DIR) && cmake -B build && cmake --build build -j4

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< -D VISUALIZE=$(if $(VISUALIZE),1,0) 

$(NAME): $(LIBFT) $(MLX_LIB) $(OBJS) $(HEADERS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(C_MLX) -o $(NAME)

clean:
	@rm -rf $(OBJS)
	@rm -rf $(LIBMLX)/build

fclean: clean
	@rm -rf $(NAME)

re: clean all

.PHONY: all, clean, fclean, re, libmlx

NAME		= fdf
CC			= cc
CFLAGS		= -Wextra -Wall -Werror -O2 -Ofast #-g -fsanitize=address -Wunreachable-code 
LIBFT		= ./lib/libft
LIBMLX		= ./lib/MLX42
RM			= rm -rf

HEADERS	= -I ./includes -I $(LIBMLX)/include

LIBS	= $(LIBMLX)/build/libmlx42.a -lglfw -pthread -lm -L"/opt/homebrew/Cellar/glfw/3.4/lib/" #-ldl

SOURCES = src/main.c \

OBJS	= $(SOURCES:.c=.o)

all: $(NAME)

$(LIBFT)/libft.a:
	@make -C $(LIBFT)

$(LIBMLX)/build/libmlx42.a:
	@cmake $(LIBMLX) -B $(LIBMLX)/build
	@make -C $(LIBMLX)/build -j4

%.o: %.c
	$(CC) $(CFLAGS) $(HEADERS) -o $@ -c $<

$(NAME): $(OBJS) $(LIBFT)/libft.a $(LIBMLX)/build/libmlx42.a
	$(CC) $(OBJS) $(LIBFT)/libft.a $(LIBS) -o $(NAME) 

clean:
	@$(RM) $(OBJS)
	@$(RM) $(LIBMLX)/build
	@make -C $(LIBFT) fclean

fclean: clean
	@rm -rf $(NAME)

re: clean all

.PHONY: re fclean clean all

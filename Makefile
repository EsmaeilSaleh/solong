NAME := so_long

CC := cc
CFLAGS := -Wall -Wextra -Werror

SRC := \
	src/main.c \
	src/read_file.c \
	src/map_read.c \
	src/map_validate.c \
	src/path_check.c \
	src/render.c \
	src/input.c \
	src/cleanup.c \
	src/utils.c

OBJ := $(SRC:.c=.o)

LIBFT_DIR := libft
LIBFT := $(LIBFT_DIR)/libft.a

MLX_DIR := minilibx-linux
MLX_LIB := $(MLX_DIR)/libmlx_Linux.a
MLX_FLAGS := -L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm -lz

INCLUDES := -Iinclude -I$(LIBFT_DIR) -I$(MLX_DIR)

all: $(NAME)

$(NAME): $(LIBFT) $(MLX_LIB) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean
	rm -f $(OBJ)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus

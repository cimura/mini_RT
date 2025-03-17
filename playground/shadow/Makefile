NAME    := exc
CC      := cc
SRCS    := main.c ft_mlx.c vector.c light.c
LIBFT_DIR := libft
LIBFT    := $(LIBFT_DIR)/libft.a
MLX_INC  := ../../mlx
MLX      := $(MLX_INC)/libmlx.a

FLAGS   := -g -Wall -Wextra -Werror
OBJS    := $(SRCS:%.c=%.o)

UNAME_S := $(shell uname -s)

# OSに応じたフラグ設定
ifeq ($(UNAME_S), Darwin)  # macOSの場合
    LD_FLAGS := $(MLX) -L$(MLX_INC) -lmlx -framework OpenGL -framework AppKit
else ifeq ($(UNAME_S), Linux)
    LD_FLAGS := -L$(MLX_INC) -lmlx -lX11 -lXext -lm
endif

%.o: %.c
	$(CC) $(FLAGS) -I$(MLX_INC) -I$(LIBFT_DIR) -c $< -o $@

all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) bonus

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(LIBFT) $(LD_FLAGS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME) $(LIBFT)

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re

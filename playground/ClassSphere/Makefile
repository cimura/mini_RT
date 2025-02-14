NAME    := exc
CC      := cc
SRCS    := main.c ft_mlx.c map.c vector.c
MLX_INC := ../../mlx
MLX     := $(MLX_INC)/libmlx.a

FLAGS   := -g -Wall -Wextra -Werror
OBJS    := $(SRCS:%.c=%.o)

UNAME_S := $(shell uname -s)

# OSに応じたフラグ設定
ifeq ($(UNAME_S), Darwin)  # macOSの場合
    LD_FLAGS := ../../mlx/libmlx.a -L../mlx -lmlx -framework OpenGL -framework AppKit
else ifeq ($(UNAME_S), Linux)
    LD_FLAGS := -L../mlx -lmlx -lX11 -lXext -lm
endif

%.o: %.c
	$(CC) $(FLAGS) -I$(MLX_INC) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LD_FLAGS) -o $(NAME)

clean:
	rm -f $(OBJS) $(NAME)

fclean:
	rm -f $(OBJS) $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY:	all clean fclean re
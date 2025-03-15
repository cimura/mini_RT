<<<<<<< HEAD
NAME    := exc
CC      := cc
SRCS    := display.c ft_mlx.c main.c map.c vector.c
MLX_INC := ../mlx
MLX     := $(MLX_INC)/libmlx.a
=======
NAME    	:= exc
CC      	:= cc
SRCS    	:= display.c ft_mlx.c libft2.c main.c map.c parse_objects.c parser.c vector.c
MLX_INC 	:= ../mlx
MLX     	:= $(MLX_INC)/libmlx.a
LIBFT_DIR	:=	./libft
LIBFT		:=	$(LIBFT_DIR)/libft.a
>>>>>>> ad29cdf (ambient_lightning構造体のparserが完成)

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
NAME    	:= exc
CC      	:= cc
SRCS    	:= display.c ft_mlx.c libft2.c libft3.c main.c map.c parse_objects.c parser.c vector.c
MLX_INC 	:= ../mlx
MLX     	:= $(MLX_INC)/libmlx.a
LIBFT_DIR	:=	./libft
LIBFT		:=	$(LIBFT_DIR)/libft.a

FLAGS   	:= -g -Wall -Wextra -Werror
IFLAGS		:=	-I$(LIBFT_DIR)/inc/
LFLAGS		:=	-L$(LIBFT_DIR) -lft
OBJS    	:= $(SRCS:%.c=%.o)

UNAME_S		:= $(shell uname -s)

# OSに応じたフラグ設定
ifeq ($(UNAME_S), Darwin)  # macOSの場合
    LD_FLAGS := ../../mlx/libmlx.a -L../mlx -lmlx -framework OpenGL -framework AppKit
else ifeq ($(UNAME_S), Linux)
    LD_FLAGS := -L../mlx -lmlx -lX11 -lXext -lm
endif

%.o: %.c
	$(CC) $(FLAGS) -I$(MLX_INC) $(IFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(OBJS) $(LD_FLAGS) -o $(NAME) $(LFLAGS)

$(LIBFT):
	$(MAKE) bonus -C $(LIBFT_DIR)

clean:
	rm -f $(OBJS) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean:
	rm -f $(OBJS) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY:	all clean fclean re

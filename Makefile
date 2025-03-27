NAME		:=	exc
CC			:=	cc
INC_DIR		:=	inc/
SRC_DIR		:=	src/
SRC			:=	calculate_phong_radiance.c camera.c dcolor.c cylinder_utils.c cylinder.c \
				display.c ft_mlx.c intersections.c libft2.c libft3.c main.c parse_objects.c \
				parser.c plane.c renderer.c sphere.c utils.c vector.c
OBJ_DIR		:=	obj/
OBJ			:=	$(addprefix $(OBJ_DIR), $(SRC:.c=.o))
LIBFT_DIR	:=	libft/
LIBFT		:=	$(LIBFT_DIR)libft.a
MLX_DIR		:=	mlx/
MLX			:=	$(MLX_DIR)libmlx.a

DFLAGS		:=	-g
CFLAGS		:=	-Wall -Wextra -Werror $(DFLAGS)
IFLAGS		:=	-I$(INC_DIR) -I$(LIBFT_DIR)$(INC_DIR) -I$(MLX_DIR)

UNAME_S		:=	$(shell uname -s)

# OSに応じたフラグ設定
ifeq ($(UNAME_S), Darwin)  # macOSの場合
    LD_FLAGS := $(MLX_DIR)libmlx.a -L$(MLX_DIR) -lmlx -L/usr/X11R6/lib -lXext -lX11 -lm -lz
else ifeq ($(UNAME_S), Linux)
    LD_FLAGS := -L$(MLX_DIR) -lmlx -lX11 -lXext -lm
endif

LFLAGS		:=	-L$(LIBFT_DIR) -lft $(LD_FLAGS)

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	mkdir -p $@

$(NAME): $(OBJ_DIR) $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(IFLAGS) $(OBJ) -o $@ $(LFLAGS)

$(LIBFT):
	$(MAKE) bonus -C $(LIBFT_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

clean:
	$(MAKE) $@ -C $(LIBFT_DIR)
	rm -rf $(OBJ_DIR)

fclean:	clean
	$(MAKE) $@ -C $(LIBFT_DIR)
	rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re

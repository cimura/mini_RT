NAME		:=	miniRT
CC			:=	cc
INC_DIR		:=	inc/
SRC_DIR		:=	src/
SRC			:=	camera.c catadioptric_utils.c catadioptric.c cylinder_utils.c cylinder.c \
				dcolor.c display.c ft_mlx.c intersections.c libft2.c libft3.c main.c material.c \
				parse_objects_utils.c parse_objects.c parse_scene.c parser_utils.c parser.c plane.c \
				renderer.c shader.c skybox.c sphere.c texture_mapping.c texture_register.c texture.c \
				utils.c vector_utils.c vector.c
OBJ_DIR		:=	obj/
OBJ			:=	$(addprefix $(OBJ_DIR), $(SRC:.c=.o))
LIBFT_DIR	:=	libft/
LIBFT		:=	$(LIBFT_DIR)libft.a
MLX_DIR		:=	mlx/
MLX			:=	$(MLX_DIR)libmlx.a

DFLAGS		:=	-g -O3 -MMD
CFLAGS		:=	-Wall -Wextra -Werror $(DFLAGS)
IFLAGS		:=	-I$(INC_DIR) -I$(LIBFT_DIR)$(INC_DIR) -I$(MLX_DIR)

STB_DIR		:=	$(INC_DIR)
STB_HEADER	:=	$(STB_DIR)stb_image.h
STB_URL		:=	https://raw.githubusercontent.com/nothings/stb/master/stb_image.h

MLX_URL		:=	https://github.com/42Paris/minilibx-linux.git

UNAME_S		:=	$(shell uname -s)

ifeq ($(UNAME_S), Darwin)
    LD_FLAGS := $(MLX_DIR)libmlx.a -L$(MLX_DIR) -lmlx -L/usr/X11R6/lib -lXext -lX11 -lm -lz
else ifeq ($(UNAME_S), Linux)
    LD_FLAGS := -L$(MLX_DIR) -lmlx -lX11 -lXext -lm
endif

LFLAGS		:=	-L$(LIBFT_DIR) -lft $(LD_FLAGS)

all: $(STB_HEADER) $(MLX) $(OBJ_DIR) $(NAME)

-include $(OBJ_DIR)/*.d

$(OBJ_DIR):
	mkdir -p $@

$(NAME): $(OBJ_DIR) $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(IFLAGS) $(OBJ) -o $@ $(LFLAGS)

$(STB_HEADER):
	@echo "Downloading stb_image.h..."
	@mkdir -p $(STB_DIR)
	@curl -fsSL $(STB_URL) -o $(STB_HEADER)

$(MLX):
	@echo "Cloning MiniLibX..."
	@git clone $(MLX_URL) $(MLX_DIR)
	@$(MAKE) -C $(MLX_DIR)

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

memory: fclean
	$(MAKE) CFLAGS="$(CFLAGS) -g -fsanitize=address"

.PHONY:	all clean fclean re

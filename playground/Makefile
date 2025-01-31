NAME	:=	exc

CC	:=	cc

SRCS	:=	FirstSample.c
MLX_INC	:=	../mlx
MLX	:=	$(MLX_INC)/libmlx.a

LD_FLAGS	:= -lX11 -lXext -lm
FLAGS	:=	-g -Wall -Wextra -Werror
OBJS	:=	$(SRCS:%.c=%.o)

all:	$(NAME)

$(NAME):	$(SRCS)
	$(CC) $(FLAGS) $(SRCS) -I$(MLX_INC) -o $(NAME) $(MLX) $(LD_FLAGS)

clean:
	rm $(OBJS) $(NAME)

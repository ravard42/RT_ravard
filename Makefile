CC = gcc
NAME = RT
FLAGS = -Wall -Wextra -O2
#FLAGS = -Wall -Wextra -g -fsanitize=address
SRC = srcs/main.c\
	srcs/init/env_init.c\
	srcs/init/parsing/parsing.c\
	srcs/init/parsing/tools.c\
	srcs/init/parsing/setting/cam_init.c\
	srcs/init/parsing/setting/cam_set.c\
	srcs/init/parsing/setting/plan_set.c\
	srcs/init/parsing/setting/sphere_set.c\
	srcs/init/parsing/setting/ondePlane_set.c\
	srcs/texture/load_png.c\
	srcs/intersection/inter.c\
	srcs/intersection/plan_inter.c\
	srcs/intersection/sphere_inter.c\
	srcs/intersection/ondePlane_inter.c\
	srcs/render/rt.c\
	srcs/render/dashboard.c\
	srcs/mlx_stuff/hook_func.c\
	srcs/mlx_stuff/loop.c\
	srcs/libmath/mat_ope.c\
	srcs/libmath/vect_ope.c\
	srcs/libmath/vect_tools.c\
	

OBJ = $(SRC:.c=.o)

INCL = -I ./ -I libft/include -I includes 
LIB = -lm -L libft -lft -lxml2  -lpng -L ./ -lmlx -lX11 -lXext

#INCL = -I includes/ -I /usr/local/include
#LIB = -L libft/ -lft -L /usr/local/lib -lmlx -framework OpenGL -framework AppKit

all : $(NAME)

$(NAME) : ./libft/libft.a $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(FLAGS) $(INCL) $(LIB)

./libft/libft.a : 
	make -C libft/

%.o : %.c
	$(CC) -o $@ -c $< $(FLAGS) $(INCL) 

clean : 
	rm -f $(OBJ)
	make -C libft/ fclean

fclean : clean
	rm -f $(NAME)

re : fclean $(NAME)

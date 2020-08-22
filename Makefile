CC = gcc
NAME = RT
FLAGS = -Wall -Wextra -O2
SRC = srcs/main.c\
	srcs/vect_and_mat/mat_ope.c\
	srcs/vect_and_mat/vect_ope.c\
	srcs/vect_and_mat/vect_tools.c\
	srcs/parsing/parsing.c\
	srcs/parsing/tools.c\
	srcs/setting/cam_init.c\
	srcs/setting/cam_set.c\
	srcs/setting/plan_set.c\
	srcs/setting/sphere_set.c\
	srcs/texture/load_png.c\
	srcs/intersection/inter.c\
	srcs/intersection/plan_inter.c\
	srcs/intersection/sphere_inter.c\
	srcs/pixel/rt.c\
	srcs/mlx_stuff/env_init.c\
	srcs/mlx_stuff/hook_func.c\
	srcs/mlx_stuff/loop.c\
	

OBJ = $(SRC:.c=.o)

INCL = -I ./ -I includes 
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

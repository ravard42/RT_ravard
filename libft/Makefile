CC = gcc
FLAGS = -Wall -Wextra -O2
NAME = libft.a
SRC =	v_abs_diff.c\
	ft_rm_whitespace.c\
	ft_rm_space_at_the_beginning.c\
	ft_revstr.c\
	ft_rm_multi_space.c\
	ft_power.c\
	ft_memset.c\
	ft_bzero.c\
	ft_memcpy.c\
	ft_memccpy.c\
	ft_memmove.c\
	ft_memchr.c\
	ft_memcmp.c\
	ft_strlen.c\
	ft_strdup.c\
	ft_strcpy.c\
	ft_strncpy.c\
	ft_strcat.c\
	ft_strncat.c\
	ft_strlcat.c\
	ft_strchr.c\
	ft_strrchr.c\
	ft_strstr.c\
	ft_strnstr.c\
	ft_strcmp.c\
	ft_strncmp.c\
	ft_atoi.c\
	ft_atof.c\
	ft_isalpha.c\
	ft_isdigit.c\
	ft_isxdigit.c\
	ft_isalnum.c\
	ft_isascii.c\
	ft_isprint.c\
	ft_toupper.c\
	ft_tolower.c\
	ft_memalloc.c\
	ft_memdel.c\
	ft_strnew.c\
	ft_strdel.c\
	ft_strclr.c\
	ft_striter.c\
	ft_striteri.c\
	ft_strmap.c\
	ft_strmapi.c\
	ft_strequ.c\
	ft_strnequ.c\
	ft_strsub.c\
	ft_strjoin.c\
	ft_strsplit.c\
	ft_strsplit_list.c\
	ft_itoa.c\
	ft_strtrim.c\
	ft_putchar.c\
	ft_putstr.c\
	ft_putendl.c\
	ft_putnbr.c\
	ft_putchar_fd.c\
	ft_putstr_fd.c\
	ft_putendl_fd.c\
	ft_putnbr_fd.c\
	ft_lstnew.c\
	ft_lstdelone.c\
	ft_lstdel.c\
	ft_lstadd.c\
	ft_lstiter.c\
	ft_lstmap.c\
	get_next_line.c\

OBJ = $(SRC:.c=.o)
INCLUDE = ../includes


all: $(NAME)

$(NAME): $(OBJ)
	ar -r $(NAME) $^

%.o: %.c
	$(CC) -o $@ -c $< -I $(INCLUDE) $(FLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)
.PHONY: all clean fclean re

SRC_S = ./ft_memset.c \
			./ft_bzero.c \
			./ft_strlen.c \
			./ft_strlcpy.c \
			./ft_strchr.c \
			./ft_strncmp.c \
			./ft_atoi.c \
			./ft_isalpha.c \
			./ft_isdigit.c \
			./ft_strdup.c \
			./ft_strjoin.c \
			./ft_itoa.c \
			./ft_putstr_fd.c \
			./ft_strchr.c \
			./get_next_line.c \
			./ft_split_str.c \
			./ft_putchar.c \
			./ft_strcmp.c
			
NAME = libft.a
CC = gcc
CFLAGS = -g -Wall -Wextra -Werror -I$(INC)

OBJ_S = $(SRC_S:.c=.o)

OBJ_BONUS = $(SRC_BONUS:.c=.o)

INC = ./libft.h 

all: $(NAME)

$(NAME):  $(OBJ_S)
	ar rcs $(NAME) $(OBJ_S)

./%.o: ./%.c $(INC)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f *.o

fclean: clean
	@rm -f $(NAME)

re: fclean all

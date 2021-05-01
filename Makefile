.PHONY: all clean fclean re

PARS_P = ./parse/

PARS_SRCS = dollar.c	 \
			env.c		 \
			parse.c		 \
			set_units.c  \
			shlvl.c 	 \
			space_line.c \
			utils.c 

INC = ./minishell.h
LIBFT_A = $(LIBFT_P)libft.a
LIBFT_P = ./libft/
NAME = minishell.a
CC = gcc
CFLAGS = -g -I$(INC)

OBJS = $(PARS_OBJS:.c=.o) 
PARS_OBJS =	$(addprefix $(PARS_P), $(PARS_SRCS))
all : $(NAME)

$(NAME) : $(OBJS) 
		make -C ./libft
		mv $(LIBFT_A) $(NAME)
		ar rcs $(NAME) $(OBJS)
		$(CC) -g main.c $(NAME) -o minishell

%.o: %.c $(INC)
	$(CC) $(CFLAGS) -c $< -o $@

clean : 
		make clean -C $(LIBFT_P)
		@rm -f $(OBJS)

fclean : clean
		make fclean -C $(LIBFT_P)
		@rm -f $(NAME)

re : fclean all

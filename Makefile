.PHONY: all clean fclean re

PARS_P = ./parse/
TERM_P = ./termcap/
LOGIC_P = ./logic/
EXEC_P = ./exec/

PARS_SRCS = dollar.c	 \
			env.c		 \
			parse.c		 \
			set_units.c  \
			shlvl.c 	 \
			space_line.c \
			utils.c 	 \
			check_valid.c

TERM_SRCS = button_arrow.c \
			button_spec.c \
			termcap.c \
			termcap_flag.c \
			signals.c

LOGIC_SRCS = built_in.c\
            ft_lstadd_back.c\
            ft_lstnew.c\
            echo.c\
            exit.c\
            envv.c\
            pwd.c\
            export.c\
            export_one_arg.c\
            unset.c\
            ft_putnbr.c\
			cd.c

EXEC_SRCS = init.c \
			redir_pipe.c \
			exec_cmd.c \
			exec_execve.c \
			utils.c

INC = ./minishell.h
LIBFT_A = $(LIBFT_P)libft.a
LIBFT_P = ./libft/
NAME = minishell.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -I$(INC) 

OBJS = $(PARS_OBJS:.c=.o) $(TERM_OBJS:.c=.o)  $(EXEC_OBJS:.c=.o) $(LOGIC_OBJS:.c=.o)

PARS_OBJS =	$(addprefix $(PARS_P), $(PARS_SRCS))
TERM_OBJS =	$(addprefix $(TERM_P), $(TERM_SRCS))
LOGIC_OBJS = $(addprefix $(LOGIC_P), $(LOGIC_SRCS))
EXEC_OBJS = $(addprefix $(EXEC_P), $(EXEC_SRCS))

all : $(NAME)

$(NAME) : $(OBJS) main.c
		make -C ./libft
		mv $(LIBFT_A) $(NAME)
		ar rcs $(NAME) $(OBJS)
		$(CC) -g main.c $(NAME) -o minishell -ltermcap

%.o: %.c $(INC)
	$(CC) $(CFLAGS) -c $< -o $@ 

clean : 
		make clean -C $(LIBFT_P)
		@rm -f $(OBJS)

fclean : clean
		make fclean -C $(LIBFT_P)
		@rm -f $(NAME)

re : fclean all

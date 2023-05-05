# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kakumar <kakumar@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/13 18:42:58 by jofoto            #+#    #+#              #
#    Updated: 2023/05/05 17:17:08 by kakumar          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS =				-Wall -Wextra -Werror -g\
					-lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include

SRC =				main.c builtins/pwd.c builtins/echo.c builtins/exit.c builtins/env.c \
					builtins/export.c builtins/export_without_args.c\
					parsing/check_commands.c parsing/quote_parser.c parsing/check_unclosed_quotes.c \
					parsing/string_len_without_quotes.c interactive/signals.c \
					interactive/terminal_handles.c parsing/tokenize.c parsing/tokenize_helpers.c \
					parsing/init_realloc_vectors.c list_utils/list_utils.c list_utils/new_node_utils.c \
					

OBJ =				$(SRC:%.c=%.o)

NAME =				minishell

LIBFT =				libft/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	cc -o $(NAME) $(OBJ) $(FLAGS) $(LIBFT)

$(OBJ): %.o: %.c
	cc -c $? -o $@

$(LIBFT):
	cd libft && $(MAKE)

clean:
	rm -f $(OBJ)
	cd libft && $(MAKE) clean

fclean: clean
	rm -f $(NAME)
	cd libft && $(MAKE) fclean

re: fclean all
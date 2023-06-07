# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kakumar <kakumar@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/13 18:42:58 by jofoto            #+#    #+#              #
#    Updated: 2023/06/07 09:59:22 by kakumar          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS =				-Wall -Wextra -Werror \
					-lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include

SRC =				main.c builtins/pwd.c builtins/echo.c builtins/exit.c builtins/env.c \
					builtins/export.c builtins/export_without_args.c builtins/unset.c builtins/cd.c\
					signals/signals.c tree/tree_making.c tree/exec_tree.c tree/exec_tree_helpers.c\
					signals/terminal_handles.c parsing/tokenize.c parsing/tokenize_helpers.c \
					parsing/init_realloc_vectors.c list_utils/list_utils.c list_utils/new_node_utils.c \
					tree/tree_making_helpers.c parsing/tokenize_env.c helpers.c tree/exec_tree_operations.c \
					tree/exec_tree_operations_utils.c \
					

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
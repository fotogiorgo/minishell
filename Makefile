# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/13 18:42:58 by jofoto            #+#    #+#              #
#    Updated: 2023/04/25 14:53:41 by jofoto           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS =				-Wall -Wextra -Werror -g -fsanitize=address \
					-lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include



SRC =				main.c interactive/interactive.c builtins/pwd.c check_commands.c

OBJ =				$(SRC:%.c=%.o)

NAME =				minishell

LIBFT =				libft/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	cc -o $(NAME) $(OBJ) $(LIBFT) $(FLAGS)

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
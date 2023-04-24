# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/13 18:42:58 by jofoto            #+#    #+#              #
#    Updated: 2023/04/24 14:04:02 by jofoto           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS =				-Wall -Wextra -Werror -lreadline

SRC =				main.c

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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakumar <kakumar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 13:25:28 by kakumar           #+#    #+#             */
/*   Updated: 2023/04/26 11:37:55 by kakumar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "../libft/libft.h"
# include <readline/readline.h> //readline
# include <readline/history.h> //add history
# include <signal.h>
# include <termios.h>

#define MAXIN 1024 // maxinput

//builtins
void	get_pwd(char *str);
void	get_echo(char *input);
void	exit_func(void);

//parsing
void	check_command_from_input(char *input);
char	*return_wrong_input(char *input);
int		check_quotes(char *input);
char	*remove_quotes(char *input);
int		length_without_quotes(char *input);

//interactive
void	init_signals(void);
void	rl_replace_line (const char *text, int clear_undo);
#endif
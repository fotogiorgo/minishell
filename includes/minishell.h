/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/04/25 14:54:09 by jofoto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "../libft/libft.h"
# include <readline/readline.h> //readline
# include <readline/history.h> //add history
# include <signal.h>

/* # include <stdlib.h>
# include <unistd.h>
#include <sys/types.h>
#include <sys/select.h>
#include <locale.h> */ 

#define MAXIN 1024 // maxinput

void	get_pwd(void);
void	check_command_from_input(char *input);
void	init_signals(void);
void	rl_replace_line (const char *text, int clear_undo);

#endif
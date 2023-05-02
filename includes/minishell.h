/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 13:25:28 by kakumar           #+#    #+#             */
/*   Updated: 2023/05/02 19:43:28 by jofoto           ###   ########.fr       */
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

typedef struct	s_argv_vec
{
	char	**argv;  //argc
	int		curr;	//argc
	int		cap;
}				t_argv_vec;

typedef struct	s_token_vec
{
	char	*token;
	int		curr;
	int		cap;
}				t_token_vec;

/* typedef	struct s_tree
{
	int		type;				// = #DEFINE PIPE
	char	*func_to_exec;		// NULL in a case of pipe
	char	**argv_for_func;	// "blah blah" int case of echo
	int		fd_of_redirect;
	t_tree	*left;				// NULL in case of executable (echo)
	t_tree	*right;				// NULL in case of executable (echo)
}				t_tree; */


//builtins
void	get_pwd(char *str);
void	get_echo(char *input);
void	exit_func(void);

//parsing
void	check_command_from_input(char *input);
int		tokenize_input(char *str, t_argv_vec	*argv);
void	init_vec(t_argv_vec	*argv);
void	init_token(t_token_vec	*tkn_vec);
void	realloc_vector(t_argv_vec	*argv);
void	realloc_token(t_token_vec	*tkn_vec);
void	free_argv(t_argv_vec	*argv);
void	add_char_to_token(char	**str, t_token_vec	*tkn_vec);
void	add_nl_to_token(t_token_vec	*tkn_vec);

//interactive
void	init_signals(void);
void	init_terminal(void);
void	rl_replace_line (const char *text, int clear_undo);
void	disable_enable_echoctl(int enable);
#endif
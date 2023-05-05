/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakumar <kakumar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 13:25:28 by kakumar           #+#    #+#             */
/*   Updated: 2023/05/05 14:52:11 by kakumar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
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

typedef struct s_envp_list
{
	int					index;
	char				*variable;
	char				*key;
	char				*value;
	struct s_envp_list	*next;
}				t_envp_list;

typedef struct s_data
{
	t_argv_vec	*argv;
	t_envp_list	*envp_list;
	char		**our_envp;
	int			num_of_env_var;
	int			exit_code;
}				t_data;

/* typedef	struct s_tree
{
	int		type;				// = #DEFINE PIPE
	char	*func_to_exec;		// NULL in a case of pipe
	char	**argv_for_func;	// "blah blah" int case of echo
	int		fd_of_redirect;
	t_tree	*left;				// NULL in case of executable (echo)
	t_tree	*right;				// NULL in case of executable (echo)
}				t_tree; */

//delete later
void	print_argv(t_argv_vec	argv);

//list
t_envp_list	*ft_newlst(char	*str, int i);
void		ft_add_back(t_envp_list	**lst, char *str, int i);
t_envp_list	*create_our_envp(t_data *data, char **envp);
char		*get_key(char *str);
char		*get_value(char *str);

//builtins
void	get_pwd(char *str);
void	get_echo(t_argv_vec *argv);
void	get_all_env(t_envp_list **envps);
void	export_var(t_data *data);
void	export_without_args(t_data *data);
void	exit_func(void);

//parsing
void	check_command_from_input(t_data *data, t_argv_vec	*argv);
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
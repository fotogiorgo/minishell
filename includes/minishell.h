/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 13:25:28 by kakumar           #+#    #+#             */
/*   Updated: 2023/05/30 18:41:46 by jofoto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libft/libft.h"
# include <readline/readline.h> //readline
# include <readline/history.h> //add history
# include <signal.h>
# include <termios.h>
# include <dirent.h>
# include <fcntl.h>
# include <errno.h>

# define MAXIN 1024 // maxinput
# define OPERATORS ">|<"

# define PIPE		1
# define EXEC		2
# define BI_EXEC	3
# define REDIR		4
# define HEREDOC	5

typedef struct s_argv_vec
{
	char	**argv;	//argv
	int		curr;	//argc
	int		cap;
}				t_argv_vec;

typedef struct s_token_vec
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

typedef	struct s_tree
{
	int				type;				// = #DEFINE PIPE
	char			*func_to_exec;		// NULL in a case of pipe
	char			**argv_for_func;	// "blah blah" int case of echo
	int				argv_cap;
	int				argv_curr;
	struct s_tree	*left;				// NULL in case of executable (echo)
	struct s_tree	*right;				// NULL in case of executable (echo)
}				t_tree;

typedef struct s_data
{
	t_argv_vec	*argv;
	t_envp_list	*envp_list;
	int			num_of_env_var;
	int			exit_code;
	int			default_stdout;
	int			default_stdin;
}				t_data;

t_data	g_data;

//delete later
void	print_argv(t_argv_vec	argv);
void	print_tree(t_tree *tree);

//list
t_envp_list	*ft_newlst(char	*str, int i);
void		ft_add_back(t_envp_list	**lst, char *str, int i);
t_envp_list	*create_our_envp(char **envp);
char		*get_key(char *str);
char		*get_value(char *str);
char		*get_value_from_key(char *key);
//builtins
void	get_cd(char **argv);
void	get_pwd(void);
void	get_echo(char **argv);
void	get_all_env(void);
void	export_var(char **argv);
void	export_without_args(char **argv);
int		check_key_in_export(char *key, char *str);
void	unset_var(char **argv);
void	exit_func(char **argv);

//parsing
void	check_command_from_input(t_argv_vec	*argv);
int		tokenize_input(char *str, t_argv_vec	*argv);
void	init_vec(t_argv_vec	*argv);
void	init_token(t_token_vec	*tkn_vec);
void	add_env_var(char **str, t_token_vec *tkn_vec);
void	realloc_vector(t_argv_vec	*argv);
void	realloc_token(t_token_vec	*tkn_vec);
void	free_argv(t_argv_vec	*argv);
void	add_char_to_token(char	**str, t_token_vec	*tkn_vec);
void	add_nl_to_token(t_token_vec	*tkn_vec);

//tree
t_tree	*make_tree(t_argv_vec *argv);
t_tree	*parce_exec(t_argv_vec *argv);
char	*check_path(char *path, char *command);
char	*get_path(char	*command);
void	exec_tree(t_tree *tree);
int		validate_redir_file(char *file);
int		get_args(t_argv_vec *argv, t_tree *tree);
int		init_tree_args(t_tree *tree);
int		add_remainder_to_beginning(t_argv_vec *argv, t_tree *tree);

//interactive
void	init_signals(void);
void	init_terminal(void);
void	rl_replace_line(const char *text, int clear_undo);
void	disable_enable_echoctl(int enable);
void	init_heredoc_sigs(void);

//helpers
int	fork_wrapper_with_sigs(void);
#endif
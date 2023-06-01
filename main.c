/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakumar <kakumar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 13:21:19 by kakumar           #+#    #+#             */
/*   Updated: 2023/06/01 11:23:05 by kakumar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	init_shell(void)
{
	init_terminal();
	init_signals();
}

void	ctrl_d_handler(t_argv_vec *argv)
{
	disable_enable_echoctl(1);
	write(1, "exit\n", 6);
	exit(1);
}

int	take_input(char *str, t_argv_vec *argv)
{
	char	*buff;

	buff = readline("minishell$ ");
	if (buff == NULL)
		ctrl_d_handler(argv);
	else
	{
		if (ft_strlen(buff) < 1)
		{
			free(buff);
			return (0);
		}
		add_history(buff);
		if (tokenize_input(buff, argv) == 0)
		{
			free_argv(argv);
			return (0);
		}
	}
	return (1);
}

void	init_data(t_argv_vec *argv, char **envp)
{
	g_data.argv = argv;
	g_data.num_of_env_var = 0;
	g_data.envp_list = NULL;
	g_data.envp_list = create_our_envp(envp);
	g_data.exit_code = 0;
	g_data.default_stdout = dup(STDOUT_FILENO);
	g_data.default_stdin = dup(STDIN_FILENO);
	return ;
}

/* void	print_tree(t_tree *tree)
{
	if(tree->right)
		print_tree(tree->right);
	if(tree->type == PIPE)
		printf("PIPE \n");
	else if (tree->type == REDIR)
		printf("REDIR \n");
	else
	{
		printf("%s \n", tree->func_to_exec);
		if(tree->argv_for_func)
		{
			for(int i = 0; tree->argv_for_func[i]; i++)
				printf("(%s) \n", tree->argv_for_func[i]);
		}
	}
	if(tree->left)
		print_tree(tree->left);
} */

void	print_tree(t_tree *tree)
{
	if (tree->right)
		print_tree(tree->right);
	if (tree->type == PIPE)
		write(1, "PIPE ", 6);
	else if (tree->type == REDIR)
		write(1, "REDIR ", 6);
	else if (tree->type == HEREDOC)
		write(1, "HEREDOC ", 8);
	else
	{
		write(1, "EXEC ", 6);
		if (tree->argv_for_func)
		{
			for (int i = 0; tree->argv_for_func[i]; i++)
				write(1, "arg ", 4);
		}
	}
	write(1, "\n", 1);
	if (tree->left)
		print_tree(tree->left);
}

void	free_tree(t_tree *tree)
{
	if (tree && tree->right)
		free_tree(tree->right);
	if (tree && tree->left)
		free_tree(tree->left);
	if (tree && tree->argv_for_func)
		free(tree->argv_for_func);
	if (tree)
		free(tree);
}

int main(int argc, char **argv1, char **envp)
{
	char		input_str[MAXIN];
	t_argv_vec	argv;
	t_argv_vec	holder;
	t_tree		*tree;

	(void) argv1;
	(void) argc;
	init_data(&argv, envp);
	while (1)
	{
		init_shell();
		if (!take_input(input_str, &argv))
		{
			// free_argv(&argv);
			continue ;
		}
		// print_argv(argv);
		holder = argv;
		// printf("argvcurr: %i || gdata argvcurr: %i\n", argv.curr, g_data.argv->curr);
		tree = make_tree(&argv); // what if maketree doesnt return
		// print_tree(tree);
		signal(SIGINT, SIG_IGN);
		disable_enable_echoctl(1);
		exec_tree(tree);
		free_tree(tree);
		// printf("are we here\n");
		free_argv(&holder);
	}
}
/* change the wrapper to set the signals to default and see what the 
heredoc does */
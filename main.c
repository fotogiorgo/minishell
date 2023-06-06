/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakumar <kakumar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 13:21:19 by kakumar           #+#    #+#             */
/*   Updated: 2023/06/06 09:54:43 by kakumar          ###   ########.fr       */
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
	g_data.parent_pid = getpid();
	return ;
}

int	main(int argc, char **argv1, char **envp)
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
			continue ;
		holder = argv;
		tree = make_tree(&argv);
		signal(SIGINT, SIG_IGN);
		disable_enable_echoctl(1);
		exec_tree(tree);
		free_tree(tree);
		free_argv(&holder);
	}
}
/* change the wrapper to set the signals to default and see what the 
heredoc does */
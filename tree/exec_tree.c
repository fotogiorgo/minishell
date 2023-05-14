/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 18:57:56 by jofoto            #+#    #+#             */
/*   Updated: 2023/05/14 11:59:01 by jofoto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	panic(char *error_str)
{
	write(2, error_str, ft_strlen(error_str));
	exit(1);
}

/* command cant be freed cause process gets replaced with execve
we can just replace "func_to_exec" wit it if needed */
void	exec_ve(t_tree *tree)
{
	char	*command;

	command = get_path(tree->argv_for_func[0]);
	if(fork_wrapper() == 0)
	{
		execve(command, tree->argv_for_func, NULL);
		write(2, "minishell: ", 11);
		write(2, tree->argv_for_func[0], ft_strlen(tree->argv_for_func[0]));
		write(2, ": command not found\n", 20);
	}
	wait(NULL);
	free(command);
}
/* we might have an issue here with the -1 */
void	exec_builtin_leaf(t_tree *tree)
{
	tree->argv_for_func++;
	if (ft_strncmp_case_ins(tree->argv_for_func[-1], "echo", 5) == 0)
		get_echo(tree->argv_for_func);
	else if (ft_strncmp_case_ins(tree->argv_for_func[-1], "exit", 5) == 0)
		exit_func();
	else if (ft_strncmp_case_ins(tree->argv_for_func[-1], "export", 7) == 0)
		export_var(tree->argv_for_func);
	else if (ft_strncmp_case_ins(tree->argv_for_func[-1], "pwd", 4) == 0)
		get_pwd();
	else if (ft_strncmp_case_ins(tree->argv_for_func[-1], "env", 4) == 0)
		get_all_env();
	else if (ft_strncmp_case_ins(tree->argv_for_func[-1], "cd", 3) == 0)
		get_cd(tree->argv_for_func);
	else if (ft_strncmp_case_ins(tree->argv_for_func[-1], "unset", 6) == 0)
		unset_var(tree->argv_for_func);
}

void	exec_pipe(t_tree *tree)
{
	int	p[2];

	if(pipe(p) < 0)
		exit(1);
	if(fork_wrapper() == 0)
	{
		dup2(p[0], 0);
		close(p[0]);
		close(p[1]);
		exec_tree(tree->left);
	}
	if(fork_wrapper() == 0)
	{
		dup2(p[1], 1);
		close(p[0]);
		close(p[1]);
		exec_tree(tree->right);
	}
	close(p[0]);
	close(p[1]);
	wait(NULL);
	wait(NULL);
}


static void	handle_signal(int sig)
{
	if(sig == 2)
		write(1, "\n", 1);	
	exit(1);
}

void	init_heredoc_sigs(void)
{
	struct sigaction	sa;

	disable_enable_echoctl(0);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = handle_signal;
	signal(SIGQUIT, SIG_IGN);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGTSTP, &sa, NULL);
}

void	exec_heredoc(t_tree *tree)
{
	char	*line;
	int		p[2];

	init_heredoc_sigs();
	if(pipe(p) < 0)
		exit(1);
	write(1, "> ", 2);
	line = get_next_line(0);
	while (ft_strncmp(tree->argv_for_func[1], line, ft_strlen(tree->argv_for_func[1])) != 0
			|| line[ft_strlen(tree->argv_for_func[1])] != '\n')
	{
		write(p[1], line, ft_strlen(line));
		free(line);
		write(1, "> ", 2);
		line = get_next_line(0);
	}
	free(line);
	dup2(p[0], 0);
	close(p[0]);
	close(p[1]);
	disable_enable_echoctl(1);
	set_child_sigs();
	exec_tree(tree->right);
}

/* does it have to be in a child process? */
void	exec_redir(t_tree *tree)
{
	int	fd;

	//if (fork_wrapper() == 0)
	//{
		if (ft_strncmp(tree->argv_for_func[0], ">", 2) == 0)
		{
			fd = open(tree->argv_for_func[1], O_CREAT | O_TRUNC | O_WRONLY, 0644);
			dup2(fd, 1);
		}
		else if (ft_strncmp(tree->argv_for_func[0], ">>", 2) == 0)
		{
			fd = open(tree->argv_for_func[1], O_CREAT | O_APPEND | O_WRONLY, 0644);
			dup2(fd, 1);
		}
		else if (ft_strncmp(tree->argv_for_func[0], "<", 2) == 0)
		{
			fd = open(tree->argv_for_func[1], O_RDONLY);
			if (fd == -1)
				panic("file does not exist");
			dup2(fd, 0);
		}
		close(fd);
		exec_tree(tree->right);
	//};
	//wait(NULL);
}

void	exec_tree(t_tree *tree)
{
	if (tree->type == BI_EXEC)
		exec_builtin_leaf(tree);
	else if (tree->type == EXEC)
		exec_ve(tree); 
	else if (tree->type == PIPE)
		exec_pipe(tree);
	else if(tree->type == REDIR)
		exec_redir(tree);
	else if(tree->type == HEREDOC)
		exec_heredoc(tree);
	exit(1);
}

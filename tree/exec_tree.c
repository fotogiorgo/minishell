/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakumar <kakumar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 18:57:56 by jofoto            #+#    #+#             */
/*   Updated: 2023/05/28 18:32:01 by kakumar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	panic(char *error_str)
{
	write(2, error_str, ft_strlen(error_str));
	exit(1);
}

void	check_exit_status(void)
{
	if (WIFEXITED(g_data.exit_code))
		return ;
	else if (WIFSIGNALED(g_data.exit_code))
	{
		if (WTERMSIG(g_data.exit_code) == 2)
			write(2, "\n", 1);
		else if (WTERMSIG(g_data.exit_code) == 3)
			write(1, "Quit: 3\n", 9);
		g_data.exit_code += 128;
	}
}

/* command cant be freed cause process gets replaced with execve
we can just replace "func_to_exec" wit it if needed */
void	exec_ve(t_tree *tree)
{
	char	*command;

	command = get_path(tree->argv_for_func[0]);
	if(fork_wrapper_with_sigs() == 0)
	{
		execve(command, tree->argv_for_func, NULL);
		write(2, "minishell: ", 11);
		write(2, tree->argv_for_func[0], ft_strlen(tree->argv_for_func[0]));
		write(2, ": command not found\n", 20);
		exit(127);
	}
	wait(&(g_data.exit_code));
	g_data.exit_code = g_data.exit_code % 255;
	check_exit_status();
	free(command);
}

/* we might have an issue here with the -1 */
void	exec_builtin_leaf(t_tree *tree)
{
	tree->argv_for_func++;
	if (ft_strncmp_case_ins(tree->argv_for_func[-1], "echo", 5) == 0)
		get_echo(tree->argv_for_func);
	else if (ft_strncmp_case_ins(tree->argv_for_func[-1], "exit", 5) == 0)
		exit_func(tree->argv_for_func);
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

	if (pipe(p) < 0)
		exit(1);
	if(fork_wrapper_with_sigs() == 0)
	{
		dup2(p[0], 0);
		close(p[0]);
		close(p[1]);
		exec_tree(tree->left);
		exit(0);
	}
	if(fork_wrapper_with_sigs() == 0)
	{
		dup2(p[1], 1);
		close(p[0]);
		close(p[1]);
		exec_tree(tree->right);
		exit(0);
	}
	close(p[0]);
	close(p[1]);
	wait(&(g_data.exit_code));
	wait(&(g_data.exit_code));
}

void	pipe_heredoc_line(t_tree *tree)
{
	char	*line;
	int		p[2];

	if(pipe(p) < 0)
		exit(1);
	line = readline("> ");
	/* if (line == NULL)
		write(1, "\033[1A\033[2C", 9); */
	while (line && ft_strncmp(tree->argv_for_func[1], line, ft_strlen(tree->argv_for_func[1])) != 0)
	{
		write(p[1], line, ft_strlen(line));
		write(p[1], "\n", 1);
		free(line);
		line = readline("> ");
		/* if (line == NULL)
			write(1, "\033[1A\033[2C", 9); */
	}
	if (line)
		free(line);
	dup2(p[0], 0);
	close(p[0]);
	close(p[1]);
}

void	exec_heredoc(t_tree *tree)
{
	if (fork_wrapper_with_sigs() == 0)
	{
		init_heredoc_sigs();
		pipe_heredoc_line(tree);
		disable_enable_echoctl(1);
		exec_tree(tree->right);
		exit(0);
	}
	wait(&(g_data.exit_code));
	g_data.exit_code = g_data.exit_code % 255;
}

void	exec_redir(t_tree *tree)
{
	int	fd;

	if (fork_wrapper_with_sigs() == 0)
	{
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
		exit(0);
	}
	wait(&(g_data.exit_code));
}

void	exec_tree(t_tree *tree)
{
	if(tree == NULL)
		return ;
	else if (tree->type == BI_EXEC)
		exec_builtin_leaf(tree);
	else if (tree->type == EXEC)
		exec_ve(tree);
	else if (tree->type == PIPE)
		exec_pipe(tree);
	else if (tree->type == REDIR)
		exec_redir(tree);
	else if (tree->type == HEREDOC)
		exec_heredoc(tree);
	return ;
}

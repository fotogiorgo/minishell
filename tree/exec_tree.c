/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakumar <kakumar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 18:57:56 by jofoto            #+#    #+#             */
/*   Updated: 2023/06/02 10:11:03 by kakumar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	panic(char *error_str)
{
	write(2, "minishell: ", 12);
	write(2, error_str, ft_strlen(error_str));
	write(2, ": No such file or directory\n", 29);
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

void	exec_ve(t_tree *tree)
{
	char	*command;

	command = get_path(tree->argv_for_func[0]);
	if (fork_wrapper_with_sigs() == 0)
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
	// free(command);
}

void	exec_builtin_leaf(t_tree *tree)
{
	if (ft_strncmp_case_ins(*(tree->argv_for_func), "echo", 5) == 0)
		get_echo(tree->argv_for_func + 1);
	else if (ft_strncmp_case_ins(*(tree->argv_for_func), "exit", 5) == 0)
		exit_func(tree->argv_for_func + 1);
	else if (ft_strncmp_case_ins(*(tree->argv_for_func), "export", 7) == 0)
		export_var(tree->argv_for_func + 1);
	else if (ft_strncmp_case_ins(*(tree->argv_for_func), "pwd", 4) == 0)
		get_pwd();
	else if (ft_strncmp_case_ins(*(tree->argv_for_func), "env", 4) == 0)
		get_all_env();
	else if (ft_strncmp_case_ins(*(tree->argv_for_func), "cd", 3) == 0)
		get_cd(tree->argv_for_func + 1);
	else if (ft_strncmp_case_ins(*(tree->argv_for_func), "unset", 6) == 0)
		unset_var(tree->argv_for_func + 1);
}

void	exec_tree(t_tree *tree)
{
	if (tree == NULL)
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

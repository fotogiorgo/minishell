/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree_operations.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakumar <kakumar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 09:13:16 by kakumar           #+#    #+#             */
/*   Updated: 2023/06/02 09:35:32 by kakumar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_pipe(t_tree *tree)
{
	int	p[2];

	if (pipe(p) < 0)
		exit(1);
	if (fork_wrapper_with_sigs() == 0)
	{
		dup2(p[1], 1);
		close(p[0]);
		close(p[1]);
		exec_tree(tree->right);
		exit(0);
	}
	wait(&(g_data.exit_code));
	if (fork_wrapper_with_sigs() == 0)
	{
		dup2(p[0], 0);
		close(p[0]);
		close(p[1]);
		exec_tree(tree->left);
		exit(0);
	}
	close(p[0]);
	close(p[1]);
	wait(&(g_data.exit_code));
}

void	exec_heredoc(t_tree *tree)
{
	int		p[2];

	if (fork_wrapper_with_sigs() == 0)
	{
		if (pipe(p) < 0)
			exit(1);
		init_heredoc_sigs();
		pipe_heredoc_line(tree, p);
		close(p[0]);
		close(p[1]);
		disable_enable_echoctl(1);
		exec_tree(tree->right);
		exit(0);
	}
	wait(&(g_data.exit_code));
	g_data.exit_code = g_data.exit_code % 255;
}

void	choose_redir(t_tree *tree)
{
	int	fd;

	if (ft_strncmp(tree->argv_for_func[0], ">", 2) == 0)
	{
		fd = open(tree->argv_for_func[1], \
		O_CREAT | O_TRUNC | O_WRONLY, 0644);
		dup2(fd, 1);
	}
	else if (ft_strncmp(tree->argv_for_func[0], ">>", 2) == 0)
	{
		fd = open(tree->argv_for_func[1], \
		O_CREAT | O_APPEND | O_WRONLY, 0644);
		dup2(fd, 1);
	}
	else if (ft_strncmp(tree->argv_for_func[0], "<", 2) == 0)
	{
		fd = open(tree->argv_for_func[1], O_RDONLY);
		if (fd == -1)
			panic(tree->argv_for_func[1]);
		dup2(fd, 0);
	}
	close(fd);
}

void	exec_redir(t_tree *tree)
{
	if (fork_wrapper_with_sigs() == 0)
	{
		choose_redir(tree);
		exec_tree(select_next(tree->right));
		exit(0);
	}
	wait(&(g_data.exit_code));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree_operations_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakumar <kakumar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 09:20:08 by kakumar           #+#    #+#             */
/*   Updated: 2023/06/02 09:31:01 by kakumar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_tree	*select_next(t_tree *tree)
{
	int	fd;

	while (tree && tree->type == REDIR)
	{
		if (ft_strncmp(tree->argv_for_func[0], ">", 2) == 0)
			fd = open(tree->argv_for_func[1], \
			O_CREAT | O_TRUNC | O_WRONLY, 0644);
		else if (ft_strncmp(tree->argv_for_func[0], ">>", 2) == 0)
			fd = open(tree->argv_for_func[1], \
			O_CREAT | O_APPEND | O_WRONLY, 0644);
		else if (ft_strncmp(tree->argv_for_func[0], "<", 2) == 0)
		{
			fd = open(tree->argv_for_func[1], O_RDONLY);
			if (fd == -1)
				panic(tree->argv_for_func[1]);
		}
		close(fd);
		tree = tree->right;
	}
	return (tree);
}

void	pipe_heredoc_line(t_tree *tree, int p[2])
{
	char	*line;

	if (fork_wrapper_with_sigs() == 0)
	{
		dup2(g_data.default_stdout, 1);
		dup2(g_data.default_stdin, 0);
		line = readline("> ");
		while (line && ft_strncmp(tree->argv_for_func[1], \
		line, ft_strlen(tree->argv_for_func[1]) + 1) != 0)
		{
			write(p[1], line, ft_strlen(line));
			write(p[1], "\n", 1);
			free(line);
			line = readline("> ");
		}
		if (line)
			free(line);
		close(p[0]);
		close(p[1]);
		exit(1);
	}
	wait(NULL);
	dup2(p[0], 0);
}

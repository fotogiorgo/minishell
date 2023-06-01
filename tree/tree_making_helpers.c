/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_making_helpers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakumar <kakumar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 13:53:53 by jofoto            #+#    #+#             */
/*   Updated: 2023/06/01 09:01:56 by kakumar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	validate_redir_file(char *file, int type)
{
	if (type == HEREDOC)
		return (1);
	if (*file == '\n' || *file == '\0')
	{
		write(2, "minishell: syntax error near \
		unexpected token `newline\'\n", 59);
		return (0);
	}
	else if (is_char_in_set(*file, OPERATORS))
	{
		write(2, "minishell: syntax error near unexpected token `", 47);
		write(2, file, 1);
		write(2, "\'\n", 2);
		return (0);
	}
	return (1);
}

int	init_tree_args(t_tree *tree)
{
	tree->argv_for_func = ft_calloc(sizeof(char *), 5);
	if (tree->argv_for_func == NULL)
		return (0);
	tree->argv_cap = 5;
	tree->argv_curr = 0;
	return (1);
}

int	more_args(t_argv_vec *argv)
{
	if (argv->curr <= 0 || !argv->argv[0])
		return (0);
	if (is_char_in_set(argv->argv[0][0], \
	OPERATORS) && ft_strlen(argv->argv[0]) < 3
	&& argv->argv[0][ft_strlen(argv->argv[0]) + 1] == 'o')
		return (0);
	return (1);
}

int	get_args(t_argv_vec *argv, t_tree *tree)
{
	while (more_args(argv))
	{
		if (tree->argv_curr == tree->argv_cap - 1)
		{
			tree->argv_for_func = (char **)realloc_two_d \
			((void **)tree->argv_for_func, tree->argv_cap - 1);
			if (tree->argv_for_func == NULL)
				return (0);
		}
		tree->argv_for_func[tree->argv_curr] = argv->argv[0];
		tree->argv_curr++;
		argv->argv++;
		argv->curr--;
	}
	return (1);
}

int	add_remainder_to_beginning(t_argv_vec *argv, t_tree *tree)
{
	t_tree	*new_node;

	if (more_args(argv) == 0)
		return (1);
	while (tree && tree->right && tree->right->type != PIPE)
		tree = tree->right;
	if (!tree || (tree->type != EXEC && tree->type != BI_EXEC))
	{
		new_node = parce_exec(argv);
		tree->right = new_node;
		return (1);
	}
	else if (!get_args(argv, tree))
		return (0);
	return (1);
}

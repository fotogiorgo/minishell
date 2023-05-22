/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_making_helpers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 13:53:53 by jofoto            #+#    #+#             */
/*   Updated: 2023/05/22 14:19:18 by jofoto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	validate_redir_file(char *file)
{
	if (*file == '\n' || *file == '\0')
	{
		write(2, "minishell: syntax error near \
		unexpected token `newline\'\n", 57);
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

int	get_args(t_argv_vec *argv, t_tree *tree)
{
	while (argv->curr > 0 && argv->argv[0] && \
	!is_char_in_set(argv->argv[0][0], OPERATORS))
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
	if(tree == NULL)
		return (1);
	while (tree->right)
		tree = tree->right;
	if (!get_args(argv, tree))
		return (0);
	return (1);
}

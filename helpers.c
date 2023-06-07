/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakumar <kakumar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 18:47:11 by jofoto            #+#    #+#             */
/*   Updated: 2023/06/07 10:08:36 by kakumar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	fork_wrapper_with_sigs(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		write(2, "fork error\n", 12);
		exit(1);
	}
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	return (pid);
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

void	free_argv(t_argv_vec *argv)
{
	int	i;

	i = 0;
	if (argv->argv == NULL)
		return ;
	while (i < argv->curr)
	{
		free(argv->argv[i]);
		argv->argv[i] = NULL;
		i++;
	}
	free(argv->argv);
	argv->cap = 0;
	argv->curr = 0;
	argv->argv = NULL;
}

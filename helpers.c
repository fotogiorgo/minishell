/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakumar <kakumar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 18:47:11 by jofoto            #+#    #+#             */
/*   Updated: 2023/05/15 14:46:29 by kakumar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	fork_wrapper_with_sigs(void)
{
	int	pid;

	pid = fork();
	if(pid == -1)
	{
		write(2, "fork error\n", 12);
		exit(1);
	}
	if (pid == 0)
		set_child_sigs();
	return (pid);
}
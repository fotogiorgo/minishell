/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:39:10 by kakumar           #+#    #+#             */
/*   Updated: 2023/05/14 12:55:04 by jofoto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_func(void)
{
	disable_enable_echoctl(1);
	write(2, "exit\n", 6);
	exit(1);
	//kill(getppid(), SIGTSTP);
}
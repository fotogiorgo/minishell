/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:24:37 by jofoto            #+#    #+#             */
/*   Updated: 2023/05/14 20:24:55 by jofoto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_signal(int sig)
{
	if(sig == 2)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
		exit(1);
}

void	init_signals(void)
{
	struct sigaction	sa;

	//sa.sa_flags = SA_RESTART;
	//ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = handle_signal;
	signal(SIGQUIT, SIG_IGN);
	sigaction(SIGINT, &sa, NULL);
}

void	handle_child_signal(int sig)
{
	if(sig == SIGQUIT)
		write(1, "Quit: 3\n", 9);
	if (sig == SIGINT)
		write(1, "\n", 1);
	exit(1);
}

void	set_child_sigs(void)
{
	struct sigaction	sa;

	//sa.sa_flags = SA_RESTART;
	//ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = handle_child_signal;
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGINT, &sa, NULL);
}

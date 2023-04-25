/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:24:37 by jofoto            #+#    #+#             */
/*   Updated: 2023/04/25 14:47:57 by jofoto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_signal(int sig)
{
	printf("Caught SIGINT!\n");
	//rl_replace_line("\n", 1);
   	//rl_redisplay();
	//rl_redisplay();
}

void	init_signals(void)
{
	struct sigaction	sa;
	
	sa.sa_flags = SA_RESTART;
	//sa.sa_flags = SA_SIGINFO;
	//sa.sa_mask = SIGQUIT;
	sa.sa_handler = handle_signal;
	signal(SIGQUIT, SIG_IGN);
	sigaction(SIGINT, &sa, NULL);
}